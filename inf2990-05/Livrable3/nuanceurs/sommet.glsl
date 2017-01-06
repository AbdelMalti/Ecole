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

/// Propriétés du matériau du modèle
uniform vec3 diffuse;
uniform vec3 speculaire;
uniform vec3 ambiant;
uniform vec3 emission;
uniform float shininess;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 modelView;
uniform mat4 modelViewProjection;
uniform mat3 matrNormale;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoordIn;
layout(location = 3) in vec4 Color;
layout(location = 7) in vec3 Normal;

out vec4 couleur;
out vec3 normaleOut, directionLum, vecteurObs;

varying vec2 texCoord;

void main()
{
	gl_Position = modelViewProjection * vec4(position, 1.0);
	normaleOut = matrNormale * Normal;

	//Position du sommet
	vec3 pos = vec3(modelView*vec4(position, 1.0));

	///Direction lumi�re
	vec3 diLum = vec3((model*vec4(positionL, 1.0)).xyz - pos);
	directionLum = diLum;

	vec3 observ;
	if (obsLocal)
	{
		observ = normalize(-pos);
	}
	else
	{
		observ = vec3(0.0, 0.0, 1.0);
	}
	vecteurObs = observ;

	texCoord = texCoordIn;
	couleur = Color;
}