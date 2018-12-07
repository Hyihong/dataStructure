#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
	EH = 0, // equil 左右等高
    LH = 1,
	RH = -1
} bh_t;

typedef enum
{
	FALSE = 0,
	TRUE = 1
}bool_t;

//定义平衡二叉树结点

typedef struct VALNode {
	   int data;
       int bf; //平衡因子
	   struct VALNode *lchild, *rchild; //左孩子，右孩子
}VALNode, *PtrToVal;



void postorder1(PtrToVal T) {
	if (T->lchild ) {
		postorder1(T->lchild);
	}
	if (T->rchild ) {
		postorder1(T->rchild );
	}
	printf("%d ", T->data);
}

//右单旋(左边不平衡)
void R_Rotate(PtrToVal *p) {
	PtrToVal lc = (*p)->lchild;
	(*p)->lchild = lc->rchild;
	lc->rchild = *p;
	*p = lc;
}

//左单旋（右边不平衡 )
void L_Rotate(PtrToVal *p) {
	PtrToVal rc = (*p)->rchild;
	(*p)->rchild = rc->lchild;
	rc->lchild = *p;
	*p = rc;
}



//左平衡(先向左旋转，再想右旋转)
void LeftBalance( PtrToVal *T ) {
	PtrToVal lc = (*T)->lchild;
	PtrToVal rd = lc->rchild;
	switch (lc->bf) {
		    //树与子树的平衡因子方向一致， 都为LH,则以*T为根，整体右旋
			case LH :
				(*T)->bf = lc->bf = EH;
				R_Rotate(T); //仅仅右旋 
				break;
			case RH:
				// 树与子树的平衡因子方向不一致，所以需要调整一致后再旋转。
				// 根据判断左孩子的右子树的平衡因子，得到各个*T，和左孩子的平衡因子变化
				switch (rd->bf) {
				     case LH:
							(*T)->bf = RH;
							lc->bf = EH; 
							break;
					case EH:
						(*T)->bf = lc->bf  = EH;
						break;
					case RH: //左孩子的右子树向右倾斜，则需先做
						(*T)->bf = EH;
						lc->bf = LH;
						break;
				}
				rd->bf = EH;
				L_Rotate(&((*T)->lchild));
				R_Rotate(T);
				break;                    
	}
}


//右平衡( 先右旋后左旋）
void RightBalance(PtrToVal *T) {
	PtrToVal rc = (*T)->rchild;
	PtrToVal ld = rc->lchild;
	switch (rc->bf)
	{
	case RH:
		(*T)->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		switch (ld->bf)
		{
		case RH:
			(*T)->bf = LH;
			rc->bf = EH;
			break;
		case EH:
			(*T)->bf = rc->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			rc->bf = RH;
			break;
		}
		ld->bf = EH;
		R_Rotate(&((*T)->rchild) );
		L_Rotate( T );
		break;
	}

}

bool_t InsertAVL(PtrToVal *t, int e, bool_t* taller) { //t为二级指针
	 if ( t == NULL) { //指针的地址为NULL
		return FALSE;
	 }
	 if ( *t == NULL) { //树初始化了，但为空树
			 *t = (PtrToVal)malloc(sizeof(VALNode));
			 if (*t == NULL) { //申请空间失败
				 printf("申请空间失败");
				 return FALSE;
			 }
			 else {
				 (*t)->data = e;
				 (*t)->rchild = (*t)->lchild = NULL;
				 (*t)->bf = EH;
				 *taller = TRUE;
		       }
	 }
	 else {
		 if ((*t)->data == e) {
			   *taller = FALSE;
			   return FALSE;
		 }
		 else {
			   if( e< (*t)->data  ){
				      if (FALSE == InsertAVL(&((*t)->lchild), e, taller)) { //左子树插入失败
						  return FALSE;
					   }
					  if (*taller) {
						  switch ((*t)->bf) {
						         case LH: //左边高
									  //这里是一个回溯过程，如果子树长高了，且本来的平衡因为为-1，则该结点的平衡因子为 -2。 平衡被打破。
									  LeftBalance( t ); //左边不平衡（ 方法：先想左转后 再向右转）
									  *taller = FALSE;
									  break;
								 case EH: 
									 (*t)->bf = LH;
									 *taller = TRUE;
									 break;
								 case RH: {
									 (*t)->bf = EH;
									 *taller = FALSE;
									 break;
								 }
						   }
					  }
                }
			   else {
				   if (FALSE == InsertAVL(&((*t)->rchild), e, taller)) { //右子树插入失败
					   return FALSE;
				   }
				   if (*taller) {
					   switch ((*t)->bf) {
					             case RH:
									 RightBalance(t);
									 *taller = TRUE;
									 break;
								 case EH:
									 (*t)->bf = RH;
									 *taller = TRUE;
									 break;
								 case LH:
									 (*t)->bf = EH;
									 *taller = FALSE;
									 break;
						 }
				   }
			   }
		 }
	 }
	 return TRUE;
}



int main__val () {
	int i;
	PtrToVal T = NULL;// 平衡二叉树
	int  mockdata[7] = { 88,70,61,96,120,90,65 };


	PtrToVal root = NULL  ;
	bool_t taller = FALSE;
	for (i = 0; i <7; i++) {
	    	printf("%d", mockdata[i]);
		    InsertAVL(&root, mockdata[i], &taller);
	}
	

	postorder1(root);

	return 0;
}
