//
//  Shader.fsh
//  Nottub
//
//  Created by Axis Sivitz on 5/24/11.
//  Copyright 2011 NA. All rights reserved.
//

uniform vec4 color;
uniform sampler2D tex;

varying vec2 texCoordsVarying;


void main()
{
   /*gl_FragColor = color;*/
   gl_FragColor = texture2D(tex, texCoordsVarying) * color;
}
