/*
 * List.h
 *
 *  Created on: 18 mars 2015
 *      Author: Gabriel
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

#define typelist(name, type) \
typedef struct node_##name { \
	type value; \
	struct node_##name *next; \
} node_##name; \
 \
typedef struct list_##name { \
	unsigned int count; \
	node_##name* root; \
} list_##name; \
\
static inline list_##name* list_##name##_create(); \
static inline node_##name* node_##name##_create(type value); \
static inline void list_##name##_put(list_##name* list, type value); \
static inline int list_##name##_delete(list_##name* list, type value, int freevalue); \
static inline void node_##name##_delete(node_##name* node, int freevalue); \
static inline void list_##name##_free(list_##name* list); \
static inline void _list_##name##_rec(node_##name* node); \
\
static inline list_##name* list_##name##_create() { \
	list_##name* list = (list_##name*) malloc(sizeof(list_##name)); \
	list->count = 0; \
	list->root = NULL; \
	return list; \
} \
\
static inline node_##name* node_##name##_create(type value) { \
	node_##name* node = (node_##name*) malloc(sizeof(node_##name)); \
	node->value = value; \
	node->next = NULL; \
	return node; \
} \
\
static inline void list_##name##_put(list_##name* list, type value) { \
	node_##name* iterator = list->root; \
	if(iterator==NULL) { \
		list->root = node_##name##_create(value); \
	} \
	else { \
		while(iterator->next!=NULL) iterator=iterator->next; \
		iterator->next = node_##name##_create(value); \
	} \
	list->count++; \
} \
\
static inline int list_##name##_delete(list_##name* list, type value, int freevalue) { \
	if(list->count==0) return 0; \
	else { \
		if(list->root->value==value) { \
			node_##name* temp = list->root->next; \
			node_##name##_delete(list->root, freevalue); \
			list->root = temp; \
		} \
		else if(list->count==1) { \
			return 0; \
		} \
		else { \
			node_##name *iterator = list->root, *temp; \
			while(iterator->next->value!=value) {\
				if(iterator==NULL) return 0; \
				iterator=iterator->next; \
			} \
			temp = iterator->next; \
			iterator->next = temp->next; \
			node_##name##_delete(temp, freevalue); \
		} \
		list->count--; \
		return 0; \
	} \
} \
\
static inline void node_##name##_delete(node_##name* node, int freevalue) { \
	if(freevalue) free(node->value); \
	free(node); \
} \
\
static inline void list_##name##_free(list_##name* list) { \
	_list_##name##_rec(list->root); \
	free(list); \
} \
\
static inline void _list_##name##_rec(node_##name* node) { \
	if(node) { \
		_list_##name##_rec(node->next); \
		node_##name##_delete(node, 1); \
	} \
} \

#endif /* LIST_H_ */
