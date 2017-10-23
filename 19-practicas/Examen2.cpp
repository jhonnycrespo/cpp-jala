#include <iostream>
#include <cstdio>
#include <cstring>

//////////////////tipo de Dato////////////////
typedef union
{
    int n;
    char* s;
    float f;
    bool b;
}Data;

typedef enum
{
    INT , STRING, FLOAT , BOOL
}Datatype;

typedef struct 
{
    Data data;
    Datatype typo;

}Variant;

/////////////////////////////////////////////////

struct Variable
{
    char* nameVar;
    Variant* var;

    ///////////////Sobre carga de operadores/////////////////////

    Variable* operator+(const Variable& src)const
    {
        if(this->var->typo == STRING &&  src.var->typo == STRING )
        {
            Variable* nn = new Variable();
            nn->var->typo = STRING;
            memcpy(nn->var->data.s,this->var->data.s,strlen(this->var->data.s)+1);
            size_t len = strlen(nn->var->data.s);
            memcpy(nn->var->data.s+(len),src.var->data.s,strlen(src.var->data.s)+1 );
            
            return nn;  
        }
        else
        {
            return NULL;
        }
        if(this->var->typo == INT &&  src.var->typo == INT )
        {
            Variable* nn = new Variable();
            nn->var->typo = INT;

            nn->var->data.n = this->var->data.n + src.var->data.n;
            return nn;  
        }
        else
        {
            return NULL;
        }
    }

    Variable* operator+(const char* src)const
    {
        if(this->var->typo == STRING)
        {
            Variable* nn = new Variable();
            nn->var->typo = STRING;
            memcpy(nn->var->data.s,this->var->data.s,strlen(this->var->data.s)+1);
            size_t len = strlen(nn->var->data.s);
            memcpy(nn->var->data.s+(len),src,strlen(src)+1);
            
            return nn;  
        }
    }

    Variable* operator+(const int src)const
    {
       if(this->var->typo == INT)
        {
            Variable* nn = new Variable();
            nn->var->typo = INT;

            nn->var->data.n = this->var->data.n + src;
            return nn;  
        }
    }
    Variable* operator=(const Variable* src)
    {   
    	puts("--------------------> sobrecargando =");
        if(this->var->typo == src->var->typo )
        {
            this->var->data = src->var->data;
            return this;    
        }

    }
    Variable* operator!()
    {
    	puts("--------------------> sobrecargando !");
    	Variable* nv = new Variable();

    	nv->var->typo = BOOL;
    	nv->var->data.b = !(this->var->data.b);
        return nv;
    }
    //////////////////////////////////////////////////////////
    
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

typedef struct bst_node  
{
    void* data;  
    struct bst_node* left; 
    struct bst_node* right;
}node;

typedef struct  
{
    node* root;     
    int (*cmp)(const void*,const void*);  
    void (*f)(void *);
}bst;

void bst_init(bst* x, int(*cmp)(const void*,const void*), void(*f)(void*))
{
    x->root=NULL;
    x->cmp=cmp;
    x->f =f;
}

int bst_add_r(bst* tree, node** n, void* p)
{
    if(*n == NULL)
    {
        *n = (node*) malloc (sizeof(node));
        (*n)->left = NULL;
        (*n)->right = NULL;
        (*n)->data = p;
        return 1;
    }

    int r = tree->cmp((*n)->data,p);
    if(r == 0) 
    return 0;

    if(r > 0)
        return bst_add_r(tree,&((*n)->left),p);
    return bst_add_r(tree,&((*n)->right),p);
}

int bst_add(bst* tree, void* p)
{
	return bst_add_r(tree, &(tree->root), p);
}

void bst_iterate_r(node* n, void* tag, void(*f)(void*, const void*))
{
	if (n == NULL)
		return;

	bst_iterate_r(n->left, tag, f);
	f(tag, n->data);
	bst_iterate_r(n->right, tag, f);
}

void bst_iterate(bst* tree, void* tag, void (*f)(void*, const void*))
{
	bst_iterate_r(tree->root, tag, f);
}

void* bst_search_r(const bst* tree, const node* n, const void* s)
{
	if (n == NULL)
		return NULL;

	int c = tree->cmp(n->data, s);

	if (c == 0)
		return n->data;

	if (c > 0)
		return bst_search_r(tree, n->left, s);

	return bst_search_r(tree, n->right, s);
}

void* bst_search(const bst* p, const void* s)
{
	return bst_search_r(p, p->root, s);
}

void bst_release_r(bst* tree, node* n)
{
	if (n == NULL)
		return;

	bst_release_r(tree, n->left);
	bst_release_r(tree, n->right);
	tree->f(n->data);
	free(n);
	puts("bye Variable");
}

void bst_release(bst* tree)
{
	bst_release_r(tree, tree->root);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void show_variable(void* x, const void* s)
{
    Variable* vari = (Variable*) s;

    if(vari->var->typo == STRING)
        printf("%s: [%s]\n", vari->nameVar, vari->var->data );
    if(vari->var->typo == INT)
        printf("%s: [%d]\n", vari->nameVar, vari->var->data.n );
    if(vari->var->typo == FLOAT)
        printf("%s: [%f]\n", vari->nameVar, vari->var->data.f );
    if(vari->var->typo == BOOL)
    {
        if(vari->var->data.b)
        {
            printf("%s: [%s]\n", vari->nameVar, "false");
        }
        else
            printf("%s: [%s]\n", vari->nameVar, "true" );
    }
}

int cmp_variable(const void* a, const void* b)
{
    Variable* x = (Variable*) a;
    Variable* y = (Variable*) b;
    return strcmp( x->nameVar , y->nameVar);
}

bool cmp_varian(Variant* a, Variant* b)
{
    if(a->typo == b->typo)
    {
        return true;
    }
    return false;
}

void free_DescData(void* dato)
{
    Variable* aux = (Variable*) dato; 
    free(aux->nameVar);
    if(aux->var->typo == STRING)
    {
    	 puts("----->Cadena Liverada");
        delete aux->var->data.s;
    }
    free(aux->var);
    free(aux);
    puts("Varian Liberado"); 
}

class variable_evaluator
{

	Variable* crearVariables(const char* var)
	{
		Variable* nvar = new Variable;
        size_t len = strlen(var);
        char* ns = (char*) malloc(len+1);
        memcpy(ns,var,len+1);
        nvar->nameVar=ns;

        return nvar;
	}

    Variant* Sumar(const Variable* var1, const Variable* var2)
    {
        Variant* resultado = new Variant();
        if(var1->var->typo == STRING)
        {

            size_t lenV1 = strlen(var1->var->data.s);
            size_t lenV2 =  strlen(var2->var->data.s);
            size_t len = lenV1 + lenV2;
            char* ns = (char*) malloc(len+1);

            memcpy(ns, var1->var->data.s,lenV1+1);
            memcpy(ns+lenV1, var2->var->data.s ,lenV2+1);
            resultado->typo = STRING;
            resultado->data.s = ns;
            return resultado;
        }
        if(var1->var->typo == INT)
        {
            resultado->data.n  = var1->var->data.n + var2->var->data.n;
            resultado->typo = INT;  
            return resultado;
        }
        if(var1->var->typo == FLOAT)
        {
            resultado->data.f  = var1->var->data.f + var2->var->data.f;  
            resultado->typo = FLOAT;  
            return resultado;
        }        
    }

    Variant* Sumar(const Variable* var1, const char* var2)
    {
        Variant* resultado = new Variant();

        size_t lenV1 = strlen(var1->var->data.s);
        size_t lenV2 =  strlen(var2)-2;
        size_t len = lenV1 + lenV2;
        char* ns = (char*) malloc(len+1);
        memcpy(ns, var1->var->data.s,lenV1+1);
        memcpy(ns+lenV1, var2+1 ,lenV2);
        resultado->typo = STRING;
        resultado->data.s = ns;
        return resultado;

    }
    /////////////////

    bool isIntege( char* dato)
    {

        for (int i = 0; i < strlen(dato); ++i)
        {
            if(!isdigit(dato[i]))
            return false;
        }
        return true;
    }

    bool isFloat(char* dato)
    {
        for (int i = 0; i < strlen(dato); ++i)
        {
            if((!isdigit(dato[i])))
            {
            if(dato[i]!='.')
                return false;
            }
        }
        return true;
    }

    bool isBool(const char* dato)
    {
        if(!strcmp("true",dato))
        {
            return true;
        }
        if(!strcmp("false",dato))
        {
            return true;
        }
        return false;
    }

    bool isSTR(const char* dato)
    {
        if(dato[0] == '"' &&  dato[strlen(dato)-1]=='"')

            return true;
        return false;
    }

    bool isVar(const char* dato)
    {
        for (int i = 0; i < strlen(dato); ++i)
        {
            if(!isalpha(dato[i]) )
            {
                if(!isdigit(dato[i]))
                {
                    if (dato[i]!='_')
                    {
                        return false;
                        break;
                    }
                }
            }
        }
        return true;
    }

    bool isNegacion(const char* dato, char* op)
    {
    	if(dato[0]=='!')
    	{
    		size_t len = strlen(dato);
            memcpy(op,dato+1,len);
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }

    bool isSuma(const char* dato, char* op1 , char* op2)
    {
    	for (int i = 0; i < strlen(dato); i++)
        {
        	if(dato[i]!=' ')
        	{
        		op1[i] = dato[i];
                op1[i+1]='\0';        		
        	}

            if(dato[i] == '+')
			{
            	for ( int j = i + 1; j < strlen(dato); ++j)
            	{
            		if(dato[j]!=' ')
		        	{
		        		memcpy(op2, dato+j,  strlen(dato)-(j-1));
		        		return true;
		        	}
            	}
            	return true;
            }
        }
        return false;
    }

    bool verficar_id(const char* entrada, char* var, char* resto)
    {
        if(strlen(entrada)==0)
        return false;

        int i= 0 ;
        while(entrada[i]!= '=' && entrada[i]!= ' ' )
        {
            var[i] = entrada[i];
            i++;
        }
        var[i]='\0';
        if(i==0)
            return false;
        while(entrada[i]== '=' || entrada[i]== ' ' )
        {
            i++;
        }
        memcpy(resto, entrada+i, strlen(entrada)-(i-1));
        //resto[i]='\0';

        if(strlen(resto)==0)
            return false;
        return true;
    }

    bool isTipo(char* entrada,Variant* vv)
    {

        if(isIntege(entrada))
        {
            vv->data.n = atoi(entrada);
            vv->typo = INT;

            return true;
        }
        if(isFloat(entrada))
        {
            vv->data.f = atof(entrada);
            vv->typo = FLOAT;
            return true;
        }
        if(isBool(entrada))
        {
            if(strcmp("true",entrada))
            {
                vv->data.b = true;
            }
            else 
            {
                vv->data.b = false;
            }
            vv->typo = BOOL;
            return true;
        }

        if(isSTR(entrada))
        {
            size_t len = strlen(entrada)-2;
            char* ns = (char*) malloc(len+1);
            memcpy(ns,entrada+1,len);
            vv->data.s = ns;
            vv->typo = STRING;
            return true;
        }
        return false;
    }
  public:
    bst tree;
    variable_evaluator()
    {
        bst_init(&tree, cmp_variable,free_DescData);
    }
    ~variable_evaluator()
    {
        puts("-*-*-*-*-*-*-*- Liberando menoria -*-*-*-*-*-*-*-*-*");   
        bst_release(&tree);
        puts("Bye Arbol");
    }

    bool add(const char* entrada, char* msj)
    {
        char var[50];
        char resto[50];
        if(verficar_id(entrada , var , resto)) 
        {
            Variant* nv = new Variant();
            if(isTipo(resto, nv))// verificar si son datos primitivos
            {
                Variable* nvar = crearVariables(var);
                nvar->var = nv; 

                void* r = bst_search(&tree, nvar);
                if(r==NULL)
                {
                    bst_add(&tree, nvar);
                }
                else
                { 
                    Variable* nvar = (Variable*) r;
                    if(cmp_varian(nvar->var,nv))
                    {
                      nvar->var  = nvar->var ; 
                    }
                    else
                    {
                        size_t len = strlen(var);
                        memcpy(msj, var, len+1);
                        memcpy(msj+(len), " defined previously as",23);
                        return false;
                    }
                }
                return true;
            }
            else
            {
                if(isVar(resto)) // es variable
                {
                    Variable* nvar = crearVariables(resto);
                    void* r = bst_search(&tree, nvar);
                    if(r==NULL) // Verificar que la Variable no existe
                    {
                        memcpy(msj, "Unknown variable ' ",18);
                        memcpy(msj+18, resto , strlen(resto));
                        int lenaux= strlen(resto)+18;
                        msj[lenaux]='\'';
                        msj[lenaux+1]='\0';
                        return false;
                    }
                    else
                    {
                        ////////////si existe///////////////////
                        nvar = (Variable*) r; 

                        ////////////////////////////////
                        Variable* nvar2 = crearVariables(var);
                       
                        void* r2 = bst_search(&tree, nvar2);
                        if(r2==NULL)
                        {
                        	Variant* nvart = new Variant();

                        	nvart->typo = nvar->var->typo;
                        	nvart->data = nvar->var->data;
                        	
                            nvar2->var = nvart; 
                            bst_add(&tree, nvar2);
                            return true;
                        }
                        else
                        {
                            Variable* varB = (Variable*) r2;
                            if(cmp_varian(nvar->var,varB->var))
                            {
                                varB->var  = nvar->var ; 
                            }
                            else
                            {
                                size_t len = strlen(var);
                                memcpy(msj, var, len+1);
                                memcpy(msj+(len), " defined previously as",23);
                                return false;
                            }
                        }
                    }
                }
                else
                {
                	char op1[50];
                	char op2[50]; 
                	if(isNegacion(resto, op1))
                	{
                		if(isVar(op1))
                		{                			
                			Variable* nvar = crearVariables(op1);
		                    
		                    void* r = bst_search(&tree, nvar);
		                    if(r==NULL) // Verificar que el dato no existe
		                    {
		                    	memcpy(msj, "Cannot apply operator+ on variables of different type" , 60);
                                return false;
		                    }
		                    else
		                    {
		                       	//////////////// buscar la Variable /////
	                			Variable* variable = crearVariables(var);
			                    void* r1 = bst_search(&tree, variable);

			                    if(r1 == NULL) // Verificar que el dato no existe 
			                    {// crear nueva varrieble 
			                    	Variable* rrR = (Variable*) r;

			                    	Variant* nvart = new Variant();

		                        	nvart->typo = rrR->var->typo;
		                        	if(rrR->var->data.b)
		                        	{
		                        		nvart->data.b = false;
		                        	}
		                        	else
		                        	{
		                        		nvart->data.b = true ;
		                        	}
		                        	

		                        	variable->var = nvart;
									bst_add(&tree, variable);

                            		return true;
			                    	
			                    }
			                    else
			                    {
                                    // castear el r1 
                                    // cambiar el valor con  !
			                    	puts(var);
			                    }
		                    }
                		}
                	}

                	if(isSuma(resto,op1,op2))
                	{
                		if(isVar(op1) && isVar(op2))
                		{
                          
	                		Variable* var1 = crearVariables(op1);
	                		Variable* var2 = crearVariables(op2); 

	                		void* r1 = bst_search(&tree, var1);
	                		void* r2 = bst_search(&tree, var2);
                            if(r1 != NULL && r2 != NULL)
                            {
                                Variable* var1 = (Variable*) r1;
                                Variable* var2 = (Variable*) r2;

                                if( cmp_varian(var1->var, var2->var))
                                {
                                    Variant* resultado = new Variant();
                                    resultado = Sumar(var1, var2);

                                    Variable* nvar = crearVariables(var);
                                    nvar->var = resultado;  

                                    void* r = bst_search(&tree, nvar);

                                    if(r==NULL)
                                    {
                                        bst_add(&tree, nvar);
                                        return true;    
                                    }
                                    else
                                    {
                                    	nvar =( Variable*) r;
                                    	nvar->var = resultado;
                                    	return true;	
                                    }                                    
                                }
                                else
                                {   
                                    memcpy(msj, "Cannot apply operator+ on variables of different type" , 60);
                                    return false;
                                }
                            }
	                	}
	                	else
	                	{
	                		if(isVar(op1) && isSTR(op2))
	                		{                               
                                Variant* resultado = new Variant(); //variant
                                Variable* var1 = crearVariables(op1); 
                               	void* r1 = bst_search(&tree, var1);
		                		if(r1==NULL)
		                		{
		                			memcpy(msj, "Cannot apply operator+ on variables of different type" , 60);
                                    return false;
		                		}
		                		else
		                		{
                                    var1 = (Variable*) r1;
                                    if(var1->var->typo == STRING)
                                    {
                                        resultado = Sumar(var1, op2);
                                        Variable* nvar = crearVariables(var);
                                        nvar->var = resultado;                     
                                        void* r2 = bst_search(&tree, nvar);
                                        
                                        if(r2==NULL)
                                        {
                                            bst_add(&tree, nvar);
                                            return true;    
                                        }
                                        else
                                        {
                                            nvar = (Variable*) r2;
                                            nvar->var = resultado;
                                            return true;
                                        }
                                    }   
		                		}
		                	}
	                	}
                	}
                } 
            }
        return false;
        }
        else
        {
            if(strlen(entrada) == 0)
            {
                memcpy(msj, "Unsupported empty expression",32);
                return false;
            }
            memcpy(msj, "Syntax error",13);
            return false;
        }
    }

    void iterate_variables(void (*f)(void*, const void*))
    {
        bst_iterate(&tree, NULL, f);
    }
};

int main()
{
    const char* ops[] = {
    "a = 1",
    "b = 25",
    "c = \"Hello world\"",
    "d = a + b",
    "e = d + c",
    "f = 3.141592653",
    "g = true",
    "h = !g",
    "i = treu",
    "variable_1 = e",
    "variable_2 =",
    "= 256",
    "",
    "variable_3=a",
    "variable_4 =f",
    "variable_5= c + \" of c++ programmers\"",
    "variable_5 = variable_5 + \" using c++17\"",
    "variable_5 = 4",
    "="
    };

    variable_evaluator ve;

    char msg[256];
    for (auto& op : ops)
    {
        if (ve.add(op, msg))
        {
            printf("[OK] [%s]\n", op);
        }
        else
        {
            printf("[ERROR] [%s] Msg: [%s]\n", op, msg);
        }
    }
    puts("********");
  	ve.iterate_variables(show_variable);
}