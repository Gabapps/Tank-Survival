#include "Shader.h"

Shader* shader_create(char* vertex, char* fragment) {
	Shader *shader = (Shader*) malloc(sizeof(Shader));
	shader->vertex_shader = vertex;
	shader->fragment_shader = fragment;
	shader->program = 0;
	shader->vertex = 0;
	shader->fragment = 0;
	return shader;
}

void shader_free(Shader* shader) {
	glDeleteShader(shader->fragment);
	glDeleteShader(shader->vertex);
	glDeleteProgram(shader->program);
}


int shader_load(Shader* shader) {
    if(glIsShader(shader->vertex) == GL_TRUE)
        glDeleteShader(shader->vertex);

    if(glIsShader(shader->fragment) == GL_TRUE)
        glDeleteShader(shader->fragment);

    if(glIsProgram(shader->program) == GL_TRUE)
        glDeleteProgram(shader->program);

	if(!shader_compile(&(shader->vertex), GL_VERTEX_SHADER, shader->vertex_shader))
		return 0;

	if(!shader_compile(&(shader->fragment), GL_FRAGMENT_SHADER, shader->fragment_shader))
		return 0;

	shader->program = glCreateProgram();

	glBindAttribLocation(shader->program, 0, "in_Vertex");
	glBindAttribLocation(shader->program, 1, "in_Normal");

	glAttachShader(shader->program, shader->vertex);
	glAttachShader(shader->program, shader->fragment);

	// Linkage du programme

	glLinkProgram(shader->program);


	// Vérification du linkage

	GLint erreurLink = 0;
	glGetProgramiv(shader->program, GL_LINK_STATUS, &erreurLink);


	// S'il y a eu une erreur

	if(erreurLink != GL_TRUE)
	{
		// Récupération de la taille de l'erreur

		GLint tailleErreur = 0;
		glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &tailleErreur);


		// Allocation de mémoire

		char *error = calloc(tailleErreur + 1, sizeof(char));


		// Récupération de l'erreur

		glGetShaderInfoLog(shader->program, tailleErreur, &tailleErreur, error);
		error[tailleErreur] = '\0';


		// Affichage de l'erreur

		printf("%s\n", error);


		// Libération de la mémoire et retour du booléen false

		free(error);
		glDeleteProgram(shader->program);

		return 0;
	}

	else
		return 1;
}

int shader_compile(GLuint* shader, GLenum type, char* filename)
{
    // Création du shader
    *shader = glCreateShader(type);


    // Vérification du shader

    if(*shader == 0)
    {
        printf("Error, the shader type (%d) doesn't exist !\n", type);
        return 0;
    }


    // Flux de lecture

    FILE* file = fopen(filename, "r");


    // Test d'ouverture

    if(!file)
    {
        printf("Error, the file \"%s\" doesn't exist\n", filename);
        glDeleteShader(*shader);

        return 0;
    }


    // Strings permettant de lire le code source

    char* sourcecode;
    long endoffile;

    // Lecture

    fseek(file, 0, SEEK_END);
    endoffile = ftell(file);
    fseek(file, 0, SEEK_SET);
    sourcecode = calloc(endoffile+1, sizeof(char));
    fread(sourcecode, endoffile, sizeof(char), file);
    sourcecode[endoffile]='\0';

    const char* code = sourcecode;
    // Fermeture du fichier

    fclose(file);


    // Envoi du code source au shader

    glShaderSource(*shader, 1, &code, 0);


    // Compilation du shader

    glCompileShader(*shader);

    // Vérification de la compilation

    GLint erreurCompilation = 0;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &erreurCompilation);


    // S'il y a eu une erreur

    if(erreurCompilation != GL_TRUE)
    {
        // Récupération de la taille de l'erreur

        GLint error_length = 0;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &error_length);


        // Allocation de mémoire

        char *error = calloc(error_length + 1, sizeof(char));


        // Récupération de l'erreur

        glGetShaderInfoLog(*shader, error_length, &error_length, error);
        error[error_length] = '\0';


        // Affichage de l'erreur

        printf("%s\n", error);


        // Libération de la mémoire et retour du booléen false

        free(error);
        glDeleteShader(*shader);

        return 0;
    }


    // Sinon c'est que tout s'est bien passé

    else
        return 1;
}
