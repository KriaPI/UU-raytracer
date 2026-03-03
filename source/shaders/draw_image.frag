// Fragment shader
#version 330
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D u_texture;
uniform bool u_useGammaCorrection;

in vec2 v_texcoord;
out vec4 frag_color;

vec3 correct_gamma(vec3 color) {
    return pow(color, vec3(1.0 / 2.2));
}

void main()
{
    frag_color = texture(u_texture, v_texcoord);
    frag_color.rgb /= frag_color.a;
    if (u_useGammaCorrection) {
        frag_color.rgb = correct_gamma(frag_color.rgb);
    }

}
