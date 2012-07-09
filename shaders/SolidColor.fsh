uniform vec4 color;

varying vec2 texCoordsVarying;


void main()
{
    /*gl_FragColor = vec4(1,1,1,1);*/
    gl_FragColor = color;
}
