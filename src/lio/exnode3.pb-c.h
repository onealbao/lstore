/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_exnode3_2eproto__INCLUDED
#define PROTOBUF_C_exnode3_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Exnode3__Allocation Exnode3__Allocation;
typedef struct _Exnode3__AllocationTable Exnode3__AllocationTable;
typedef struct _Exnode3__Block Exnode3__Block;
typedef struct _Exnode3__Attribute Exnode3__Attribute;
typedef struct _Exnode3__SegmentHeader Exnode3__SegmentHeader;
typedef struct _Exnode3__JBOB Exnode3__JBOB;
typedef struct _Exnode3__LayoutSegment Exnode3__LayoutSegment;
typedef struct _Exnode3__Layout Exnode3__Layout;
typedef struct _Exnode3__View Exnode3__View;
typedef struct _Exnode3__Exnode Exnode3__Exnode;


/* --- enums --- */


/* --- messages --- */

struct  _Exnode3__Allocation {
    ProtobufCMessage base;
    int32_t id;
    int64_t size;
    int64_t max_size;
    int32_t ref_count;
    char *write_key;
    char *read_key;
    char *manage_key;
};
#define EXNODE3__ALLOCATION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__allocation__descriptor) \
    , 0, 0, 0, 0, NULL, NULL, NULL }


struct  _Exnode3__AllocationTable {
    ProtobufCMessage base;
    size_t n_allocs;
    Exnode3__Allocation **allocs;
};
#define EXNODE3__ALLOCATION__TABLE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__allocation__table__descriptor) \
    , 0,NULL }


struct  _Exnode3__Block {
    ProtobufCMessage base;
    int64_t allocation_offset;
    int64_t logical_offset;
    int64_t len;
    int32_t alloc_id;
};
#define EXNODE3__BLOCK__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__block__descriptor) \
    , 0, 0, 0, 0 }


struct  _Exnode3__Attribute {
    ProtobufCMessage base;
    char *key;
    char *value;
};
#define EXNODE3__ATTRIBUTE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__attribute__descriptor) \
    , NULL, NULL }


struct  _Exnode3__SegmentHeader {
    ProtobufCMessage base;
    char *name;
    int32_t id;
    int64_t version;
    size_t n_attr;
    Exnode3__Attribute **attr;
    char *state;
    int64_t total_size;
    char *type;
};
#define EXNODE3__SEGMENT_HEADER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__segment_header__descriptor) \
    , NULL, 0, 0, 0,NULL, NULL, 0, NULL }


struct  _Exnode3__JBOB {
    ProtobufCMessage base;
    int32_t id;
    size_t n_block;
    Exnode3__Block **block;
};
#define EXNODE3__JBOB__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__jbob__descriptor) \
    , 0, 0,NULL }


struct  _Exnode3__LayoutSegment {
    ProtobufCMessage base;
    int32_t segment_id;
    int64_t layout_offset;
    int64_t segment_offset;
    int64_t length;
};
#define EXNODE3__LAYOUT_SEGMENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__layout_segment__descriptor) \
    , 0, 0, 0, 0 }


struct  _Exnode3__Layout {
    ProtobufCMessage base;
    int32_t id;
    char *name;
    int64_t version;
    size_t n_attr;
    Exnode3__Attribute **attr;
    char *state;
    int64_t total_size;
    size_t n_segments;
    Exnode3__LayoutSegment **segments;
};
#define EXNODE3__LAYOUT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__layout__descriptor) \
    , 0, NULL, 0, 0,NULL, NULL, 0, 0,NULL }


struct  _Exnode3__View {
    ProtobufCMessage base;
    int32_t id;
    char *name;
    int64_t version;
    size_t n_attr;
    Exnode3__Attribute **attr;
    char *state;
    int64_t total_size;
    size_t n_layout_list;
    int32_t *layout_list;
};
#define EXNODE3__VIEW__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__view__descriptor) \
    , 0, NULL, 0, 0,NULL, NULL, 0, 0,NULL }


struct  _Exnode3__Exnode {
    ProtobufCMessage base;
    Exnode3__AllocationTable *table;
    size_t n_seg_headers;
    Exnode3__SegmentHeader **seg_headers;
    size_t n_jbob;
    Exnode3__JBOB **jbob;
    size_t n_layout;
    Exnode3__Layout **layout;
    size_t n_view;
    Exnode3__View **view;
    size_t n_attr;
    Exnode3__Attribute **attr;
};
#define EXNODE3__EXNODE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&exnode3__exnode__descriptor) \
    , NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL, 0,NULL }


/* Exnode3__Allocation methods */
void   exnode3__allocation__init
(Exnode3__Allocation         *message);
size_t exnode3__allocation__get_packed_size
(const Exnode3__Allocation   *message);
size_t exnode3__allocation__pack
(const Exnode3__Allocation   *message,
 uint8_t             *out);
size_t exnode3__allocation__tbx_pack_to_buffer
(const Exnode3__Allocation   *message,
 ProtobufCBuffer     *buffer);
Exnode3__Allocation *
exnode3__allocation__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__allocation__free_unpacked
(Exnode3__Allocation *message,
 ProtobufCAllocator *allocator);
/* Exnode3__AllocationTable methods */
void   exnode3__allocation__table__init
(Exnode3__AllocationTable         *message);
size_t exnode3__allocation__table__get_packed_size
(const Exnode3__AllocationTable   *message);
size_t exnode3__allocation__table__pack
(const Exnode3__AllocationTable   *message,
 uint8_t             *out);
size_t exnode3__allocation__table__tbx_pack_to_buffer
(const Exnode3__AllocationTable   *message,
 ProtobufCBuffer     *buffer);
Exnode3__AllocationTable *
exnode3__allocation__table__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__allocation__table__free_unpacked
(Exnode3__AllocationTable *message,
 ProtobufCAllocator *allocator);
/* Exnode3__Block methods */
void   exnode3__block__init
(Exnode3__Block         *message);
size_t exnode3__block__get_packed_size
(const Exnode3__Block   *message);
size_t exnode3__block__pack
(const Exnode3__Block   *message,
 uint8_t             *out);
size_t exnode3__block__tbx_pack_to_buffer
(const Exnode3__Block   *message,
 ProtobufCBuffer     *buffer);
Exnode3__Block *
exnode3__block__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__block__free_unpacked
(Exnode3__Block *message,
 ProtobufCAllocator *allocator);
/* Exnode3__Attribute methods */
void   exnode3__attribute__init
(Exnode3__Attribute         *message);
size_t exnode3__attribute__get_packed_size
(const Exnode3__Attribute   *message);
size_t exnode3__attribute__pack
(const Exnode3__Attribute   *message,
 uint8_t             *out);
size_t exnode3__attribute__tbx_pack_to_buffer
(const Exnode3__Attribute   *message,
 ProtobufCBuffer     *buffer);
Exnode3__Attribute *
exnode3__attribute__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__attribute__free_unpacked
(Exnode3__Attribute *message,
 ProtobufCAllocator *allocator);
/* Exnode3__SegmentHeader methods */
void   exnode3__segment_header__init
(Exnode3__SegmentHeader         *message);
size_t exnode3__segment_header__get_packed_size
(const Exnode3__SegmentHeader   *message);
size_t exnode3__segment_header__pack
(const Exnode3__SegmentHeader   *message,
 uint8_t             *out);
size_t exnode3__segment_header__tbx_pack_to_buffer
(const Exnode3__SegmentHeader   *message,
 ProtobufCBuffer     *buffer);
Exnode3__SegmentHeader *
exnode3__segment_header__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__segment_header__free_unpacked
(Exnode3__SegmentHeader *message,
 ProtobufCAllocator *allocator);
/* Exnode3__JBOB methods */
void   exnode3__jbob__init
(Exnode3__JBOB         *message);
size_t exnode3__jbob__get_packed_size
(const Exnode3__JBOB   *message);
size_t exnode3__jbob__pack
(const Exnode3__JBOB   *message,
 uint8_t             *out);
size_t exnode3__jbob__tbx_pack_to_buffer
(const Exnode3__JBOB   *message,
 ProtobufCBuffer     *buffer);
Exnode3__JBOB *
exnode3__jbob__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__jbob__free_unpacked
(Exnode3__JBOB *message,
 ProtobufCAllocator *allocator);
/* Exnode3__LayoutSegment methods */
void   exnode3__layout_segment__init
(Exnode3__LayoutSegment         *message);
size_t exnode3__layout_segment__get_packed_size
(const Exnode3__LayoutSegment   *message);
size_t exnode3__layout_segment__pack
(const Exnode3__LayoutSegment   *message,
 uint8_t             *out);
size_t exnode3__layout_segment__tbx_pack_to_buffer
(const Exnode3__LayoutSegment   *message,
 ProtobufCBuffer     *buffer);
Exnode3__LayoutSegment *
exnode3__layout_segment__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__layout_segment__free_unpacked
(Exnode3__LayoutSegment *message,
 ProtobufCAllocator *allocator);
/* Exnode3__Layout methods */
void   exnode3__layout__init
(Exnode3__Layout         *message);
size_t exnode3__layout__get_packed_size
(const Exnode3__Layout   *message);
size_t exnode3__layout__pack
(const Exnode3__Layout   *message,
 uint8_t             *out);
size_t exnode3__layout__tbx_pack_to_buffer
(const Exnode3__Layout   *message,
 ProtobufCBuffer     *buffer);
Exnode3__Layout *
exnode3__layout__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__layout__free_unpacked
(Exnode3__Layout *message,
 ProtobufCAllocator *allocator);
/* Exnode3__View methods */
void   exnode3__view__init
(Exnode3__View         *message);
size_t exnode3__view__get_packed_size
(const Exnode3__View   *message);
size_t exnode3__view__pack
(const Exnode3__View   *message,
 uint8_t             *out);
size_t exnode3__view__tbx_pack_to_buffer
(const Exnode3__View   *message,
 ProtobufCBuffer     *buffer);
Exnode3__View *
exnode3__view__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__view__free_unpacked
(Exnode3__View *message,
 ProtobufCAllocator *allocator);
/* Exnode3__Exnode methods */
void   exnode3__exnode__init
(Exnode3__Exnode         *message);
size_t exnode3__exnode__get_packed_size
(const Exnode3__Exnode   *message);
size_t exnode3__exnode__pack
(const Exnode3__Exnode   *message,
 uint8_t             *out);
size_t exnode3__exnode__tbx_pack_to_buffer
(const Exnode3__Exnode   *message,
 ProtobufCBuffer     *buffer);
Exnode3__Exnode *
exnode3__exnode__unpack
(ProtobufCAllocator  *allocator,
 size_t               len,
 const uint8_t       *data);
void   exnode3__exnode__free_unpacked
(Exnode3__Exnode *message,
 ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Exnode3__Allocation_Closure)
(const Exnode3__Allocation *message,
 void *closure_data);
typedef void (*Exnode3__AllocationTable_Closure)
(const Exnode3__AllocationTable *message,
 void *closure_data);
typedef void (*Exnode3__Block_Closure)
(const Exnode3__Block *message,
 void *closure_data);
typedef void (*Exnode3__Attribute_Closure)
(const Exnode3__Attribute *message,
 void *closure_data);
typedef void (*Exnode3__SegmentHeader_Closure)
(const Exnode3__SegmentHeader *message,
 void *closure_data);
typedef void (*Exnode3__JBOB_Closure)
(const Exnode3__JBOB *message,
 void *closure_data);
typedef void (*Exnode3__LayoutSegment_Closure)
(const Exnode3__LayoutSegment *message,
 void *closure_data);
typedef void (*Exnode3__Layout_Closure)
(const Exnode3__Layout *message,
 void *closure_data);
typedef void (*Exnode3__View_Closure)
(const Exnode3__View *message,
 void *closure_data);
typedef void (*Exnode3__Exnode_Closure)
(const Exnode3__Exnode *message,
 void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor exnode3__allocation__descriptor;
extern const ProtobufCMessageDescriptor exnode3__allocation__table__descriptor;
extern const ProtobufCMessageDescriptor exnode3__block__descriptor;
extern const ProtobufCMessageDescriptor exnode3__attribute__descriptor;
extern const ProtobufCMessageDescriptor exnode3__segment_header__descriptor;
extern const ProtobufCMessageDescriptor exnode3__jbob__descriptor;
extern const ProtobufCMessageDescriptor exnode3__layout_segment__descriptor;
extern const ProtobufCMessageDescriptor exnode3__layout__descriptor;
extern const ProtobufCMessageDescriptor exnode3__view__descriptor;
extern const ProtobufCMessageDescriptor exnode3__exnode__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_exnode3_2eproto__INCLUDED */