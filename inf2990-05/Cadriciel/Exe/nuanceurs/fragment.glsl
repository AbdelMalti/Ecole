#version 420

///Proprietes du modele de lumiere
uniform vec3 ambient;
uniform bool obsLocal;

/// Proptiétés de la source de lumière
uniform vec3 positionL;
uniform vec3 diffuseL;
uniform vec3 speculaireL;
uniform vec3 ambiantL;
uniform vec3 directionSpot1;
uniform vec3 directionSpot2;
uniform float angleSpot1;
uniform float angleSpot2;
uniform float exposantSpot1;
uniform float exposantSpot2;

/// Propri�t�s du matériau du mod�le
uniform vec3 diffuse;
uniform vec3 speculaire;
uniform vec3 ambiant;
uniform vec3 emission;
uniform float shininess;

uniform bool estSelectionne;

layout(binding = 0) uniform sampler2D diffuseTex;

varying vec2 texCoord;

in vec4  couleur;
in vec3 normaleOut, directionLum, vecteurObs;

out vec4 color;

vec4 coul = vec4(1.0, 0.5, 0.5, 1.0);
//vec4(0.5, 0.5, 0.5, 1.0);

vec4 calculerReflexion(in vec3 L, in vec3 N, in vec3 O)
{
	coul = vec4(emission + ambiant, 1.0) * vec4(ambiantL, 1.0);

	// composante ambiante
	coul += vec4(ambiant, 1.0) * vec4(ambiantL, 1.0);

	//composante diffuse
	coul += vec4(diffuse, 1.0) * vec4(diffuseL, 1.0) * max(0.0, dot(N, L));

	// composant spéculaire (Phong)
	float NdotHV = max(0.0, dot(reflect(-L, N), O));
	coul += vec4(speculaire, 1.0) * vec4(speculaireL, 1.0) * pow(NdotHV, shininess);

	return coul;
}

void main()
{
	vec3 L = normalize(directionLum);
	vec3 N = normalize(normaleOut);
	vec3 O = normalize(vecteurObs);

	vec4 rouge = vec4(1.0, 0.0, 0.0, 1.0);

	vec4 coultmp = calculerReflexion(L, N, O);
	coul = clamp(coultmp, 0.0, 1.0);

	vec4 coulTex = texture2D(diffuseTex, texCoord.st);
	vec4 coulMixTex = mix(couleur, coulTex, 0.5);
	//coul = calculerReflexion(L,N,O);
	//color = couleur*coul;
	//color = mix(coul, coulMixTex, 0.7);
	//color = coultmp*coulMixTex;
	//color = coultmp*coulMixTex;

	if (estSelectionne)
		color = rouge;//*coulTex;
	else
		color = mix(coul, coulMixTex, 0.7);

}