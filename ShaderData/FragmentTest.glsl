#version 330 core
out vec4 FragColor;
struct Material
{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camerapos;
uniform Material material;
void main()
{
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3f);
    vec3 ambient = lightColor * material.ambient*texture(material.diffuse, TexCoord).rgb;


    vec3 nor = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir, nor), 0.0);
    vec3 diffuse = (lightColor * diff)* texture(material.diffuse, TexCoord).rgb;

    vec3 viewDir = normalize(camerapos - FragPos);
    vec3 reLightDir = normalize(reflect(-lightDir, nor));
    float spe = pow(max(dot(reLightDir, viewDir), 0.0f), material.shininess);
    vec3 specular = lightColor * (spe * texture(material.specular,TexCoord).rgb );

    vec3 Result = ambient+diffuse+specular;
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3f) * vec4(Result, 1.0f);
     FragColor =  vec4(Result,1.0f);
}