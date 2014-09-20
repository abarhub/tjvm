#ifndef JCLASSE
#define JCLASSE

#include <stdint.h>

#include "jstr.h"

//const int magic_cst=0xCAFEBABE;
#define magic_cst (0xCAFEBABE);

struct exception_tablet{   
			uint16_t start_pc;
    	      	uint16_t end_pc;
    	      	uint16_t  handler_pc;
    	      	uint16_t  catch_type;
    	};

typedef struct exception_tablet EXCEPTION_TABLET;

struct Code_attribute {
	//uint16_t attribute_name_index;
	//uint32_t attribute_length;
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	//u1 code[code_length];
	uint8_t *code;
	uint16_t exception_table_length;
    EXCEPTION_TABLET *exception_table;
	//exception_table[exception_table_length];*/
    uint16_t attributes_count;
    //attribute_info attributes[attributes_count];
	struct attribute_info *attributes;
};

typedef struct Code_attribute CODE_ATTRIBUTE;

enum type_attribut{
	CodeAttr=1,
	ConstantAttr=2,
	ExceptionAttr=3,
	AutreAttr=4
};

struct attribute_info {
    	uint16_t attribute_name_index;
    	uint32_t attribute_length;
		uint8_t *info;
		short type_attribut;
		union {
			CODE_ATTRIBUTE *code;
		};
};

typedef struct attribute_info ATTRIBUTE_INFO;

struct field_info {
    	uint16_t access_flags;
    	uint16_t name_index;
    	uint16_t descriptor_index;
    	uint16_t attributes_count;
    	ATTRIBUTE_INFO *attributes;
};

typedef struct field_info FIELD_INFO;

struct jmethod_info {
    	uint16_t access_flags;
    	uint16_t name_index;
    	uint16_t descriptor_index;
    	uint16_t attributes_count;
    	ATTRIBUTE_INFO *attributes;
};

typedef struct jmethod_info JMETHOD_INFO;

enum cp_info_tag {
	CONSTANT_Class=7,
	CONSTANT_Fieldref=9,
	CONSTANT_Methodref=10,
	CONSTANT_InterfaceMethodref=11,
	CONSTANT_String=8,
	CONSTANT_Integer=3,
	CONSTANT_Float=4,
	CONSTANT_Long=5,
	CONSTANT_Double=6,
	CONSTANT_NameAndType=12,
	CONSTANT_Utf8=1,
};

struct cp_info {
    	uint8_t tag;
    	//u1 info[];
		union {
			/*struct {
				uint16_t len;
				char *buf;
			};*/
			uint32_t val_int;
			float val_float;
			long val_long;
			double val_double;
			uint16_t index_class_ref;
			uint16_t index_string_ref;
			struct {
				uint16_t field_index_ref1;
				uint16_t field_index_ref2;
			};
			struct {
				uint16_t method_index_ref1;
				uint16_t method_index_ref2;
			};
			struct {
				uint16_t interface_index_ref1;
				uint16_t interface_index_ref2;
			};
			struct {
				uint16_t name_index_ref1;
				uint16_t name_index_ref2;
			};
			JSTR *str;
		};
};

typedef struct cp_info CP_INFO;

struct jclass
{
	uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    uint16_t constant_pool_count;
    //cp_info        constant_pool[constant_pool_count-1];
	CP_INFO *constant_pool;
    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interfaces_count;
    //unsigned short interfaces[interfaces_count];
	uint16_t *interfaces;
    uint16_t fields_count;
	//field_info fields[fields_count];
	FIELD_INFO *fields;
    uint16_t methods_count;
    //method_info methods[methods_count];
	JMETHOD_INFO *methods;
    uint16_t attributes_count;
    //attribute_info attributes[attributes_count];
	ATTRIBUTE_INFO *attributes;
	/*u4             magic;
    u2             minor_version;
    u2             major_version;
    u2             constant_pool_count;
    cp_info        constant_pool[constant_pool_count-1];
    u2             access_flags;
    u2             this_class;
    u2             super_class;
    u2             interfaces_count;
    u2             interfaces[interfaces_count];
    u2             fields_count;
    field_info     fields[fields_count];
    u2             methods_count;
    method_info    methods[methods_count];
    u2             attributes_count;
    attribute_info attributes[attributes_count];*/
};

typedef struct jclass JCLASS;

#endif