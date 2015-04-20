/**
 * 
 * LLU.h
 *
 * Thomas Gouverneur - 2003
 **/
#ifndef _LLU_H
#define _LLU_H

#include "Exception.h"

#ifndef NULL
#define NULL 0
#endif

//--
// Class template declaration
//--

template <class I>
class 	LLU
{
	private:
		struct	DATA
		{
			I 					Item;
			struct	DATA		*next;
			struct 	DATA		*prev;
		};
		DATA	*head, *end;
		int		count;
	
	public:
		
		LLU			(void);
		~LLU		(void);
	
		int		Size	(void)const;
		I		Pop		(void);
		void	Del		(int);
		I		View	(void);
		I		Get		(int);
		void	Flush	(void);
		void	Swap	(int, int);
		void	Push	(I);
	
		void	Insert(const I, int);
		int		Delete(const I);
		
	
		// Operators:
		LLU<I> 	&operator=	(const LLU<I> &);
		I		operator[]	(int)const;	
		//friend ostream& operator<<(ostream &, const LLU<I> &);
};

/* dommage ca aurais pu etre bien...
template <class I>
ostream& operator<<(ostream &os, const LLU<I> &llu)
{
	for (int j=llu.Size(),i=0; i<j; i++)
		if (dynamic_cast<char *>(llu[i]) != NULL)
			os << *llu[i] << endl;
		else
			os << llu[i] << endl;
	return os;
}
*/

//--
// Definition of templates functions
//--


//--
// Constructor
//--
template 	<class I>
LLU<I>::LLU		(void)
{
	
	this->head	=	NULL;
	this->end	=	NULL;
	this->count	=	0;
	
	return;
}


//--
// Destructor
//--
template 	<class I>
LLU<I>::~LLU(void)
{
	if (!this->end)
		return;
	
	DATA *tmp;
	for (tmp = this->head->next; tmp ; tmp = tmp->next)
	{
		if (tmp->prev)
		{
			delete tmp->prev;
			this->head = tmp;
		}
	}
	delete tmp;
	this->head 	= 	NULL;
	this->end	= 	NULL;
	this->count	= 	0;
	return;
}


template 	<class I>
int			LLU<I>::Size		(void) const
{
	return this->count;
}


template 	<class I>
void		LLU<I>::Swap		(int i, int j)
{
	if (i > this->count && i < 0)
		return;

	if (j > this->count && j < 0)
		return;

	DATA *tmp;
	DATA *tmp2;
	I orig;
	int k;
	for (k=0, tmp = this->head; k < i; k++, tmp=tmp->next) ;
	for (k=0, tmp2 = this->head; k < j; k++, tmp2=tmp2->next) ;

	orig = tmp->Item;
	tmp->Item = tmp2->Item;
	tmp2->Item = orig;
		
	return;
}


template 	<class I>
void		LLU<I>::Del		(int i)
{
	if (i > this->count && i < 0)
		return;
	else
	{
		DATA *tmp;
		int j;
		for (j=0, tmp = this->head; j < i; j++, tmp=tmp->next) ;
			
		if (tmp->next) // pas le dernier de la list
		{
			tmp->next->prev = tmp->prev;
		}
		else	// dernier de la liste
		{
			this->end = tmp->prev;
		}
		if (tmp->prev)
		{
			tmp->prev->next = tmp->next;			
		}
		else
		{
			this->head = tmp->next;
		}
	}
	return;
}

template 	<class I>
I		LLU<I>::Pop		(void)
{
	I 	t;
	if (!this->end)
	{
		//printf("FOIRAGE BORDEL #@!\n");
		return t;
	}
	if (!this->end->prev)	// one element
	{
		t 							= 	this->end->Item;		
		delete 						this->end;
		this->end			=		NULL;
		this->head			=		NULL;
		this->count--;
		
		return 						t;
	}
	else
	{
		t							= 	this->end->Item;
		this->end 			= 	this->end->prev;
		delete 						this->end->next;
		this->end->next	=		NULL;
		this->count--;
		
		return 				t;
	}
}


template 	<class I>
I		LLU<I>::Get		(int Indice)
{
	I t;
	if (Indice >= this->count)
		throw new Exception("Out of range !");
	
	DATA *tmp;
	int i;
	for (i=0, tmp = this->head; i < Indice; i++, tmp=tmp->next) ;

	if (tmp == NULL) 
		throw new Exception("tsk.");
	
	return tmp->Item;
}


template 	<class I>
void		LLU<I>::Flush	(void)
{
	
	if (!this->end)
		return;
	
	DATA *tmp;
	for (tmp = this->head->next; tmp ; tmp = tmp->next)
	{
		if (tmp->prev)
		{
			delete tmp->prev;
			this->head = tmp;
		}
	}
	delete tmp;
	this->head 	= 	NULL;
	this->end	= 	NULL;
	this->count	= 	0;
	
	return;
}

template 	<class I>
void	LLU<I>::Push		(I Data)
{
	if (this->end)	// already one element
	{
		this->end->next						=	new DATA;
		this->end->next->prev			= this->end;
		this->end->next->Item			= Data;
		this->end								= this->end->next;
		this->end->next						= NULL;
	}
	else
	{
		this->end								= new DATA;
		this->end->prev						= NULL;
		this->end->next						= NULL;
		this->end->Item						= Data;
		this->head								= this->end;
	}
	this->count++;
	
	return;
}

template <class I>
void	LLU<I>::Insert(const I Data, int pos)
{	
	if (pos > this->count || pos < 0)
		if (pos != 0)
			throw new Exception("Out of range !");
	
	if (pos == 0) // add begin
	{
		DATA *tmp = new DATA;
		tmp->Item = Data;
		tmp->next = this->head;
		tmp->prev = NULL;
		if (this->head)
			this->head->prev = tmp;
		this->head = tmp;
		if (this->count == 0)
			this->end = this->head;
	}
	else
	if (pos == this->count) // add end
	{
		DATA *tmp = new DATA;
		tmp->Item = Data;
		this->end->next = tmp;
		this->end->next->prev = this->end;
		this->end->next->next = NULL;
		this->end = this->end->next;
	}
	else // add middle
	{
		pos--;
		DATA *tmp = this->head;
		
		for (int i=0; i < pos; i++, tmp=tmp->next) ;
		
		DATA *tmp2 = new DATA;
		tmp2->Item = Data;
		
		tmp2->next = tmp->next;
		tmp2->prev = tmp;
		tmp->next->prev = tmp2;
		tmp->next = tmp2;
	}
	this->count++;
}

template <class I>
int		LLU<I>::Delete(const I Elem)
{
	DATA *tmp = this->head;
	for (int i=0; i < this->count; i++, tmp=tmp->next)
	{
		if (tmp->Item == Elem) // delete this one
		{
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			else
				this->end = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				this->head = tmp->next;
			delete tmp;
			this->count--;
			return i+1;
		}
	}
	return -1;
}

template	<class I>
I	LLU<I>::View		(void)
{
	if (this->end)
		return this->end->Item;
	else // Revision 1.2
		throw new Exception("Empty stack !");
}


template	<class I>
LLU<I> 	&LLU<I>::operator=(const LLU<I> &Src)
{	
	Flush();
	// Revision 1.2
	if (Src.count) {
		for (DATA *tmp = Src.head; tmp ; tmp=tmp->next) {
			Push(tmp->Item);
		}
	}
	return *this;
}


template	<class I>
I	LLU<I>::operator[]	(int Indice) const
{
	// Revision 1.2
	if (Indice >= this->count || Indice < 0)
		throw new Exception("Out of range !");
	
	// Old code
	DATA *tmp;
	int i;
	for (i=0, tmp = this->head; i < Indice; i++, tmp=tmp->next) ;
	
	return tmp->Item;
}


#endif /* _LLU_H */
