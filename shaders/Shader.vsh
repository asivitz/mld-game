//
//  Shader.vsh
//  Nottub
//
//  Created by Axis Sivitz on 5/24/11.
//  Copyright 2011 NA. All rights reserved.
//

attribute vec4 position;
attribute vec2 texCoords;

uniform mat4 modelMat;
uniform mat4 viewMat;

varying vec2 texCoordsVarying;

void main()
{
    gl_Position = viewMat * modelMat * position;
    texCoordsVarying = texCoords;
}
