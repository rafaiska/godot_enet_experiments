extends Node2D

class_name RWActor

var attr_update_fn: Dictionary

var lin_vel = Vector2.ZERO
var rot_vel = 0.0

func _init() -> void:
	attr_update_fn = {'position': '_update_pos', 'lin_vel': '_update_lin_vel', 'rot_vel': '_update_rot_vel', 'scene': '_no_op'}

func update_attr(attr_name: String, value):
	if attr_name in attr_update_fn:
		callv(attr_update_fn[attr_name], [value])
	else:
		push_error('Unrecognized attr: ' + attr_name)

func _update_pos(position_: Dictionary):
	self.position = _get_vector2(position_)

func _update_lin_vel(linvel_: Dictionary):
	self.lin_vel = _get_vector2(linvel_)

func _get_vector2(value: Dictionary) -> Vector2:
	return Vector2(value['x'], value['y'])

func _update_rot_vel(rot_vel_: float):
	self.rot_vel = rot_vel_

func _physics_process(delta: float) -> void:
	if lin_vel != Vector2.ZERO:
		self.position += lin_vel * delta
	self.rotate(rot_vel * delta)

func _no_op(_param):
	pass
