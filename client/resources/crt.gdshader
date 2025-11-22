shader_type canvas_item;

uniform sampler2D SCREEN_TEXTURE : hint_screen_texture, filter_linear_mipmap;

void vertex() {
	// Called for every vertex the material is visible on.
}


void fragment() {
		float intensity = 0.1 * float(int(VERTEX.y) % 4);
		COLOR = COLOR + vec4(0, 0, 0, intensity);
		//if (int(VERTEX.y) % 2 == 0) {
			////COLOR = texture(SCREEN_TEXTURE, SCREEN_UV);
		//}
		//else {
			//COLOR = COLOR;
		//}
}


//void light() {
//	// Called for every pixel for every light affecting the material.
//	// Uncomment to replace the default light processing function with this one.
//}
