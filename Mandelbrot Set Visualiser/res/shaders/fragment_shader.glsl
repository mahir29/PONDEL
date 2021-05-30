#version 330 core
in vec4 gl_FragCoord;
 
out vec4 Frag_color;
 
uniform float u_cx = 0.0f;
uniform float u_cy = 0.0f;
uniform float u_zoom = 1.0f;
uniform int MAX_ITERATIONS = 40;

#define SIZE 1920
#define SCALE 4.5

const vec3 color_map[] = {
	{10  /255.0, 10  /255.0,  10   /255.0},
	{25  /255.0, 7   /255.0,  26   /255.0},
	{9   /255.0, 1   /255.0,  47   /255.0},
	{4   /255.0, 4   /255.0,  73   /255.0},
	{0   /255.0, 7   /255.0,  100  /255.0},
	{12  /255.0, 44  /255.0,  138  /255.0},
	{24  /255.0, 82  /255.0,  177  /255.0},
	{57  /255.0, 125 /255.0,  209  /255.0},
	{134 /255.0, 181 /255.0,  229  /255.0},
	{211 /255.0, 236 /255.0,  248  /255.0},
	{241 /255.0, 233 /255.0,  191  /255.0},
	{248 /255.0, 201 /255.0,  95   /255.0},
	{255 /255.0, 170 /255.0,  0    /255.0},
	{25 /255.0,  25  /255.0,  92   /255.0},
	{248 /255.0, 41  /255.0,  41   /255.0}
    
    
};
 
vec4 color(){
    

    float x = ((gl_FragCoord.x / SIZE - 0.55f) * u_zoom + u_cx) * SCALE;
    float y = ((gl_FragCoord.y / SIZE - 0.29f) * u_zoom + u_cy) * SCALE;
 
    int iter = 0;
    float c_real = x;
    float c_imag = y;
 
    while (iter < MAX_ITERATIONS && x * x + y * y < 4.0 ){
        float tmp_x = x;
        x = (x*x - y*y) + c_real;
        y = (2*tmp_x*y) + c_imag;
 
        ++iter;
    }
    
    if (iter == MAX_ITERATIONS){
        return vec4(  0.0f  , 0.0f , 0.0f , 1.0f);
    }

    int row_index = (iter * 100 / MAX_ITERATIONS % 15);    

    return vec4(color_map[row_index], 1.0f);
}
 
void main(){
    Frag_color = color();
}