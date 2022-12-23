//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file Tree.h
    Tree routines header

**/

#ifndef __TREE_H__
#define __TREE_H__

typedef struct _TREENODE_T TREENODE_T;
struct _TREENODE_T {
    VOID        *Data;
    TREENODE_T  *Right;
    TREENODE_T  *Left;
    TREENODE_T  *Child;
    TREENODE_T  *Parent;
};



typedef BOOLEAN (*TREE_PREDICATE1_T)(VOID *Node, VOID *Context);
typedef VOID (*TREE_CALLBACK_T)(VOID *Node, VOID *Context);

TREENODE_T* TreeCreate (TREENODE_T *Node, VOID *Data);
VOID        TreeAddChild (TREENODE_T *Parent, TREENODE_T *Child);
VOID        TreeRemove (TREENODE_T *Node);
TREENODE_T* TreeSearchSibling (TREENODE_T *Node, TREE_PREDICATE1_T Predicate, VOID *Data);
TREENODE_T* TreeSearchDeep (TREENODE_T *Node, TREE_PREDICATE1_T Predicate, VOID *Data);
VOID        TreeForEachSibling (TREENODE_T *Node, TREE_CALLBACK_T Predicate, VOID *Data);

VOID* QueueGet (QUEUE_T *Queue);
UINTN QueueSize (QUEUE_T *Queue);
VOID  QueuePut (QUEUE_T *Queue, VOID *Data);
VOID* QueueRemoveMsg (QUEUE_T *Queue, UINTN Size);
VOID  QueuePutMsg (QUEUE_T *Queue, VOID *Data, UINTN Size);

#endif //__TREE_H__

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************