#version 330 core

in vec3 fragmentPos;
in vec3 fragmentVertexNormal;
in vec4 fragmentColor;

out vec4 color;

uniform sampler2D imageTexture;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(10.0, 10.0, 10.0);

    vec3 objectColor = vec3(0.7137, 0.8471, 1.0);

    objectColor = objectColor * (0.1);
    // objectColor = vec3(1.0, 0.713, 0.757);

    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(fragmentVertexNormal);
    vec3 lightDir = normalize(lightPos - fragmentPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    // vec3 result = (ambient + diffuse) * objectColor;
    vec4 result = vec4(ambient + diffuse, 1.0) * fragmentColor;

    // color = vec4(result, 1.0);
    color = fragmentColor;
    // if (fragmentColor.r == 0.0)
    //     color = vec4(1.0, 1.0, 1.0, 1.0);
    // else
    //     color = vec4(0.0, 0.0, 0.0, 1.0);
}