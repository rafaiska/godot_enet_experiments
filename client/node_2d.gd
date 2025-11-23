extends Node2D

var conn: ENetConnection

var arena_size: float

var bg: ImageTexture
@onready var bg_sprite = $Stars/Sprite2D

var loaded_actors = {}

const BG_SIZE = 256
const STAR_DENSITY = 0.02

func create_bg_texture() -> Image:
	var image = Image.create(16*BG_SIZE, 16*BG_SIZE, false, Image.FORMAT_RGBA8)
	image.fill(Color(0, 0, 0, 0.0))
	var stars: Image = Image.load_from_file('res://assets/stars.png')
	for i in range(BG_SIZE):
		for j in range(BG_SIZE):
			if (randi() % 100) + 1 > STAR_DENSITY * 100:
				continue
			var s = randi() % 4
			image.blit_rect_mask(stars, stars, Rect2i(s*16, 0, 16, 16), Vector2i(i*16, j*16))
	return image

func _init() -> void:
	conn = ENetConnection.new()
	bg = ImageTexture.create_from_image(create_bg_texture())

func _process(_delta: float) -> void:
	if (bg != null and bg_sprite != null):
		bg_sprite.texture = bg
		bg_sprite.self_modulate = Color(0.404, 0.0, 0.902, 1.0)
		bg = null
	
	if conn.get_peers().size() < 1 or _not_connected():
		_connect()
	
	_handle_return(conn.service(0))
	#for p: ENetPacketPeer in conn.get_peers():
		#p.send(0, PackedByteArray("papa".to_multibyte_char_buffer()), ENetPacketPeer.FLAG_UNRELIABLE_FRAGMENT)

func _input(event: InputEvent) -> void:
	if event.is_action('ui_up'):
		$Camera2D.position.y -= 1
	if event.is_action('ui_down'):
		$Camera2D.position.y += 1
	if event.is_action('ui_left'):
		$Camera2D.position.x -= 1
	if event.is_action('ui_right'):
		$Camera2D.position.x += 1

func _handle_return(rdata: Array):
	if rdata[0] == ENetConnection.EVENT_CONNECT:
		print('Connected: ' + str(rdata[1]))
	if rdata[0] == ENetConnection.EVENT_RECEIVE:
		var data_packet: PackedByteArray = rdata[1].get_packet()
		_handle_data(data_packet.get_string_from_ascii())

func _handle_data(s_data: String):
	var parsed = JSON.parse_string(s_data)
	print(parsed)
	if 'mapdata' in parsed:
		_update_mapdata(parsed['mapdata'])
	if 'actordata' in parsed:
		_update_actors(parsed['actordata'])

func _update_mapdata(mapdata_s: String):
		var splitted = mapdata_s.remove_chars('() ').split('|')
		arena_size = Vector2(float(splitted[0]), float(splitted[1])).length()
	
func _update_actors(actordata: Array):
	for a: Dictionary in actordata:
		var actor: RWActor
		var actor_id = int(a['id'])
		if actor_id not in loaded_actors and 'scene' in a:
			actor = _load_actor(actor_id, a['scene'])
			if actor == null:
				return
		else:
			actor = loaded_actors[actor_id]
		for attr in a.keys():
			if attr != 'id':
				actor.update_attr(attr, a[attr])

func _load_actor(actor_id:int, scene_path: String):
	var packed: PackedScene = load('res://scene/' + scene_path)
	if packed != null:
		var new_scene = packed.instantiate()
		loaded_actors[actor_id] = new_scene
		$Actors.add_child(new_scene)

func _not_connected():
	return conn.get_peers().size() < 1

func _connect():
	conn.create_host(32, 32)
	conn.connect_to_host('127.0.0.1', 1234, 12, 0)
