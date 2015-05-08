/*
 * Mesh.c
 *
 *  Created on: 7 févr. 2015
 *      Author: Gabriel
 */

#include "Mesh.h"

Mesh* canvas;

//Private functions

float* mesh_get_vertices(Mesh* mesh);

float* mesh_get_normals(Mesh* mesh);

float* mesh_get_uvs(Mesh* mesh);

void mesh_desindex(Mesh* mesh);

void mesh_malloc_indexed(Mesh* mesh);

Mesh* mesh_create() {
	Mesh *mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->f = 0;
	mesh->v = 0;
	mesh->vn = 0;
	mesh->normals = NULL;
	mesh->vertices = NULL;
	mesh->triangles_id = NULL;
	mesh->normals_id = NULL;
	mesh->vbo = 0;

	return mesh;
}

int mesh_load_from_obj(Mesh* mesh, char* filename) {

	FILE* file = fopen(filename, "r");
	char buf[80];
	int v=0, vn=0, f=0, vt=0, i=0, res=0;


	if(!file) {
		printf("Cannot open .obj file : %s", filename);
		return 0;
	}

	//Count the vertices (v), the normals (vn) and the triangles (f)
	while(res!=-1) {
		res = fscanf(file, "%s", buf);
		if(strcmp("v", buf)==0) {
			v++;
		}
		if(strcmp("vn", buf)==0) {
			vn++;
		}
		if(strcmp("f", buf)==0) {
			f++;
		}
		if(strcmp("vt", buf)==0) {
			vt++;
		}
	}
	mesh->v=v;
	mesh->vn=vn;
	mesh->f=f;
	mesh->vt=vt;
	mesh_malloc_indexed(mesh);

	rewind(file);
	res=0;
	while(res!=-1) {
		res = fscanf(file, "%s", buf);
		if(strcmp("v", buf)==0) {
			fscanf(file, "%f %f %f\n",
					&(mesh->vertices[i*3]),
					&(mesh->vertices[i*3+1]),
					&(mesh->vertices[i*3+2]));
			i++;
			if(i==v) i=0;
		}
		if(strcmp("vn", buf)==0) {
			fscanf(file, "%f %f %f\n",
					&(mesh->normals[i*3]),
					&(mesh->normals[i*3+1]),
					&(mesh->normals[i*3+2]));
			i++;
			if(i==vn) i=0;
		}
		if(strcmp("vt", buf)==0) {
			fscanf(file, "%f %f\n",
					&(mesh->uvs[i*2]),
					&(mesh->uvs[i*2+1]));
			i++;
			if(i==vt) i=0;
		}
		if(strcmp("f", buf)==0) {
			if(vt) {
				fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
						&(mesh->triangles_id[i*3]), &(mesh->uvs_id[i*3]),&(mesh->normals_id[i*3]),
						&(mesh->triangles_id[i*3+1]), &(mesh->uvs_id[i*3+1]),&(mesh->normals_id[i*3+1]),
						&(mesh->triangles_id[i*3+2]), &(mesh->uvs_id[i*3+2]),&(mesh->normals_id[i*3+2]));
			}
			else {
				fscanf(file, "%d//%d %d//%d %d//%d\n",
						&(mesh->triangles_id[i*3]), &(mesh->normals_id[i*3]),
						&(mesh->triangles_id[i*3+1]), &(mesh->normals_id[i*3+1]),
						&(mesh->triangles_id[i*3+2]), &(mesh->normals_id[i*3+2]));
			}
			i++;
			if(i==f) i=0;
		}
	}

	fclose(file);

	mesh_desindex(mesh);

	mesh_load_vbo(mesh);
	return 1;
}

void mesh_load_vbo(Mesh* mesh) {
	glGenBuffers(1,&( mesh->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	glBufferData(GL_ARRAY_BUFFER, 3*9*mesh->f*sizeof(float), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 9*mesh->f*sizeof(float), mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 9*mesh->f*sizeof(float), 9*mesh->f*sizeof(float), mesh->normals);
	if(mesh->vt) glBufferSubData(GL_ARRAY_BUFFER,18*mesh->f*sizeof(float), 6*mesh->f*sizeof(float), mesh->uvs);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

float* mesh_get_vertices(Mesh* mesh) {
	int i,j,n=3*mesh->f;
	float* vertices = (float*)calloc(3*n, sizeof(float));
	if(!vertices)perror("Mesh malloc");

	for(i=0; i<n; i++) {
		for(j=0; j<3; j++) {
			vertices[i*3+j]=mesh->vertices[(mesh->triangles_id[i]-1)*3+j];
		}
	}

	return vertices;
}

float* mesh_get_uvs(Mesh* mesh) {
	int i,j,n=3*mesh->f;
	float *uvs = (float*)calloc(2*n, sizeof(float));
	if(!uvs)perror("Mesh malloc ");

	for(i=0; i<n; i++) {
		for(j=0; j<2; j++) {
			uvs[i*2+j]=mesh->uvs[(mesh->uvs_id[i]-1)*2+j];
		}
	}

	return uvs;
}

void mesh_desindex(Mesh* mesh) {
	float *temp_vertices = mesh->vertices, *temp_normals = mesh->normals, *temp_uvs = mesh->uvs;

	mesh->vertices = mesh_get_vertices(mesh);
	free(temp_vertices);

	if(mesh->vn) {
		mesh->normals = mesh_get_normals(mesh);
		free(temp_normals);
	}

	if(mesh->vt) {
		mesh->uvs = mesh_get_uvs(mesh);
		free(temp_uvs);
	}
}

void mesh_malloc_indexed(Mesh* mesh) {
	mesh->vertices = calloc(3*mesh->v, sizeof(float));
	mesh->normals = calloc(3*mesh->vn, sizeof(float));
	mesh->uvs = calloc(2*mesh->vt, sizeof(float));
	mesh->triangles_id = calloc(3*mesh->f, sizeof(int));
	mesh->normals_id = calloc(3*mesh->f, sizeof(int));
	mesh->uvs_id = calloc(3*mesh->f, sizeof(int));
}

float* mesh_get_normals(Mesh* mesh) {
	int i,j,n=3*mesh->f;
	float *normals = (float*)calloc(3*n, sizeof(float));
	if(!normals)perror("Mesh malloc ");

	for(i=0; i<n; i++) {
		for(j=0; j<3; j++) {
			normals[i*3+j]=mesh->normals[(mesh->normals_id[i]-1)*3+j];
		}
	}

	return normals;
}

void mesh_load_canvas() {

	canvas = (Mesh*)malloc(sizeof(Mesh));
	canvas->f = 2;
	canvas->v = 4;
	canvas->vn = 0;
	canvas->vt = 4;

	mesh_malloc_indexed(canvas);

	float vertices[] = {-0.5f,0.5f,1,   -0.5f,-0.5f,1,   0.5f,-0.5f,1,   0.5f,0.5f,1};
	float uvs[] = {0,1,   0,0,   1,0,   1,1};
	int triangles_id[] = {1,2,4,  2,4,3};
	int uvs_id[] = {1,2,4,  2,4,3};

	memcpy(canvas->vertices, vertices, canvas->v*3*sizeof(float));
	memcpy(canvas->uvs, uvs, canvas->vt*2*sizeof(float));
	memcpy(canvas->triangles_id, triangles_id, canvas->f*3*sizeof(int));
	memcpy(canvas->uvs_id, uvs_id, canvas->f*3*sizeof(int));

	mesh_desindex(canvas);
}

Mesh* mesh_get_canvas() {
	return canvas;
}

Mesh* mesh_get_text_view_canvas(const char* text) {
	int i, j,  x = 0, y = 0, count = 0;
	Mesh* mesh = mesh_create();

	mesh->f = 2 * strlen(text);
	mesh->v = 4 * strlen(text);
	mesh->vn = 0;
	mesh->vt = 4 * strlen(text);

	mesh_malloc_indexed(mesh);

	float vertices_[] = {-0.5f,0.5f,0,   -0.5f,-0.5f,0,   0.5f,-0.5f,0,   0.5f,0.5f,0};
	float uvs_[] = {0,1,   0,0,   1,0,   1,1};
	int triangles_id_[] = {1,2,4,  2,4,3};
	int uvs_id_[] = {1,2,4,  2,4,3};

	for(i=0; i<strlen(text); i++) {
		if(text[i]=='\n') {
			mesh->f-=2;
			x=0;
			y++;
		}
		else {
			int x_ascii = (unsigned char)text[i]%16, y_ascii = 15-((unsigned char)text[i]/16);
			float x_uv = (float)x_ascii/16, y_uv = (float)y_ascii/16;

			for(j=0; j<4; j++) {
				mesh->vertices[12*i+j*3] = vertices_[j*3]+(float)x;
				mesh->vertices[12*i+j*3+1] = vertices_[j*3+1]+(float)y;
				mesh->vertices[12*i+j*3+2] = 0;
				mesh->uvs[8*i+j*2] = x_uv + uvs_[j*2]/16;
				mesh->uvs[8*i+j*2+1] = y_uv + uvs_[j*2+1]/16;
			}

			for(j=0; j<6; j++) {
				mesh->triangles_id[i*6+j] = triangles_id_[j]+count*4;
				mesh->uvs_id[i*6+j] = uvs_id_[j]+count*4;
			}


			x++;
			count++;
		}
	}

	mesh_desindex(mesh);

	return mesh;
}

void mesh_free(Mesh* mesh) {
	free(mesh->vertices);
	free(mesh->normals);
	free(mesh->uvs);
	free(mesh->triangles_id);
	free(mesh->normals_id);
	free(mesh->uvs_id);
}
