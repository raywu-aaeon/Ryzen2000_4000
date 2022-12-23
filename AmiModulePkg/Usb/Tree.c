//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Tree.c
    USB tree manipulation routines

**/


#include "Uhcd.h"

#include "Tree.h"

/**
    initializes TREENODE_T structure

    @param  Node  Pointer to TREENODE_T structure
    @param  Data  Pointer to data structure specific to
                  the type of tree node

    @retval Pointer to TREENODE_T structure that was passed in as parrameter

**/

TREENODE_T*
TreeCreate (
    TREENODE_T  *Node,
    VOID        *Data
)
{
    Node->Data = Data;
    Node->Child = 0;
    Node->Right = 0;
    Node->Left = 0;
    Node->Parent = 0;
    return Node;
}


/**
    add a child node to the TREENODE_T structure

    @param    Parent  Pointer to parent TREENODE_T structure
    @param    Child   Pointer to child TREENODE_T structure

    @retval   None

**/

VOID
TreeAddChild (
    TREENODE_T  *Parent,
    TREENODE_T  *Child
)
{
    TREENODE_T* Node = Parent->Child;
    Parent->Child = Child;
    Child->Right = Node;
    if(Node != 0)
        Node->Left = Child;
    Child->Left = 0;
    Child->Parent = Parent;
}


/**
    removes a node from the tree

    @param    Node  Pointer to TREENODE_T structure

    @retval   None
**/

VOID
TreeRemove (
    TREENODE_T    *Node
)
{
    if(  Node->Right != 0){
        Node->Right->Left = Node->Left;
    }
    if(  Node->Left != 0){
        Node->Left->Right = Node->Right;
    }
    if( Node->Parent && Node->Parent->Child == Node )
        Node->Parent->Child = Node->Right;
    Node->Left = 0;
    Node->Right = 0;
    Node->Parent = 0;
}


/**
    Enumerates nodes of the tree which are direct children of
    the same parent

    @param    Node        Pointer to TREENODE_T structure
    @param    Predicate   Predicate function that is called for each node
                          and controll whether enumeration should continue
                          once predicate returns TRUE the enumeration will
    @param    Data        Pointer that is passed to predicate to maintain
                          the context of the enumeration

    @retval the node that cause enumeration to stop
**/

TREENODE_T*
TreeSearchSibling (
    TREENODE_T         *Node,
    TREE_PREDICATE1_T  Predicate,
    VOID               *Data
)
{
    TREENODE_T *Right;
    for(; Node; Node = Right){
        Right = Node->Right;
        if(Predicate(Node->Data, Data))return Node;
    }
    return NULL;
}


/**
    Enumerates nodes of the tree which are direct and indirect
    children of the same parent

    @param    Node       Pointer to TREENODE_T structure
    @param    Predicate  Predicate function that is called for each node;
                         controlls whether enumeration should continue
                         once predicate returns TRUE the enumeration will
    @param    Data       Pointer that is passed to predicate to maintain
                         the context of the enumeration

    @retval the node that cause enumeration to stop
**/

TREENODE_T*
TreeSearchDeep (
    TREENODE_T         *Node,
    TREE_PREDICATE1_T  Predicate,
    VOID               *Data
)
{
    TREENODE_T *Right;
    TREENODE_T *Child;
    for(; Node; Node=Right){
        Right = Node->Right;
        Child = Node->Child;
        if(Predicate(Node->Data, Data))return Node;
        if(Child){
            TREENODE_T* Child1 = TreeSearchDeep(Node->Child, Predicate, Data);
            if(Child1)
                return Child1;
        }
    }
    return 0;
}


/**
    Enumerates nodes of the tree which are direct children of
    the same parent; In contrust to TreeSearchSibling this
    function ignores the result returned from call-back routine
    and always enumerates all sibling nodes

    @param    Node       Pointer to TREENODE_T structure
    @param    CallBack   Call-back function that is called for each node
    @param    Data       Pointer that is passed to call-back to maintain
                         the context of the enumeration

    @retval   None

**/

VOID
TreeForEachSibling (
    TREENODE_T       *Node,
    TREE_CALLBACK_T  CallBack,
    VOID             *Data
)
{
    for(; Node; Node = Node->Right)
        CallBack(Node->Data, Data);
}


/**
    retrieves data stored at the tail of the queue and
    removes the tail item

    @param    Queue  Pointer to QUEUE_T structure

    @retval   Data   Pointer to QUEUE_T data

**/

VOID*
QueueGet (
    QUEUE_T  *Queue
)
{
    VOID* Data;
    if( Queue->Tail == Queue->Head ) return NULL;
    Data = Queue->Data[Queue->Tail++];
    if( Queue->Tail == Queue->Maxsize ) Queue->Tail -= Queue->Maxsize;
    return Data;
}


/**
    retrieves number of items stored in the queue

    @param    Queue  Pointer to QUEUE_T structure

    @retval   Size   Queue Size

**/

UINTN
QueueSize (
    QUEUE_T  *Queue
)
{
    return (Queue->Head >= Queue->Tail)? Queue->Head - Queue->Tail:
            Queue->Head  + Queue->Maxsize - Queue->Tail;
}


/**
    add a new item in front of the head of the queue

    @param    Queue  Pointer to QUEUE_T structure
    @param    Data   Pointer to QUEUE_T data

    @retval   None

**/

VOID
QueuePut (
    QUEUE_T  *Queue,
    VOID     *Data
)
{
    ASSERT(QueueSize(Queue) < Queue->Maxsize );
    Queue->Data[Queue->Head++] = Data;
    if(Queue->Head == Queue->Maxsize) Queue->Head -= Queue->Maxsize;
    if(Queue->Head == Queue->Tail){
        //Drop data from queue
        Queue->Tail++;
        if( Queue->Tail == Queue->Maxsize ) Queue->Tail -= Queue->Maxsize;
    }
}


/**
    add a variable size item to the queue

    @param    Queue  Pointer to QUEUE_T structure
    @param    Data   Pointer to data
    @param    Size   Number of dwords to add to the queue

    @retval   None

**/

VOID
QueuePutMsg (
    QUEUE_T  *Queue,
    VOID     *Data,
    UINTN    Size
)
{
    ASSERT(QueueSize(Queue) < Queue->Maxsize);
    ASSERT(Size < Queue->Maxsize);
    if(Queue->Head + Size > Queue->Maxsize)
        Queue->Head = 0;
    CopyMem( (char*)Queue->Data + Queue->Head, Data, Size );
    Queue->Head += Size;
    if(Queue->Head == Queue->Maxsize) Queue->Head = 0;
    if(Queue->Head == Queue->Tail){
        //Drop data from queue
        Queue->Tail += Size;
        if( Queue->Tail >= Queue->Maxsize ) Queue->Tail = 0;
    }
}

/**
    retrieves a variable size item from the queue

    @param    Queue  Pointer to QUEUE_T structure
    @param    Size   Number of dwords to remove from the queue

    @retval   Data   Pointer to data

**/

VOID*
QueueRemoveMsg (
    QUEUE_T  *Queue,
    UINTN    Size
)
{
    VOID* Data;
    if( Queue->Tail == Queue->Head ) return NULL;
    Data = (VOID*)((char*)Queue->Data + Queue->Tail);
    Queue->Tail += Size;
    if( Queue->Tail > Queue->Maxsize ){
        Data = (VOID*)Queue->Data;
        Queue->Tail = Size;
    } else if(Queue->Tail == Queue->Maxsize ){
        Queue->Tail = 0;
    }
    return Data;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
