#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <ctype.h>
#include <dos.h>

#define LONG 20
#define MAXUS 3
#define MAXPR 100
#define MAXCL 100

typedef struct {
    char username[LONG];
	char password[LONG];
} Usuario;

Usuario users[MAXUS];
int numusers = 0;

typedef struct{
	char code[10];
	char name[LONG];
	char telefono[9];
	char direccion[50];
	char correo[100];
	float credito;
} Cliente;

int numclientes = 0;
Cliente clientes[MAXCL];

typedef struct{
	char codigo[10];
	char nombre[LONG];
	int cantidad;
	float precio;
	char unidad[20];
	char descripcion[50];
	char dia[5];
	char mes[5];
	char year[5];
} Producto;

Producto inventario[MAXPR];
int numproductos = 0;
int numfactura = 0;

/* Prototipado de funciones */

void menuInicio(void);
void regist(void);
void login(void);

void menuPrincipal(void);

void menuInventario(void);
void agregarProducto(void);
void buscarProducto(void);
void actualizarProducto(void);
void eliminarProducto(void);
void verProducto(void);
void venderProducto(void);

void menuCliente(void);
void agregarCliente(void);
void buscarCliente(void);
void actualizarCliente(void);
void eliminarCliente(void);
void verCliente(void);

int buscarPr(char *referencia);
int buscarCl(char *referencia);
void taparProducto(int x, int y, int x2, int y2);
void taparCliente(int x, int y, int x2, int y2);

void inicio(void);
void fin(void);

/* FUNCION PRINCIPAL */

int main(void)
{
	inicio();

	menuInicio();

	fin();

    return 0;
}

/*================== FUNCIONES =====================*/

void menuInicio(void)
{
	int op;
	cleardevice();

	setbkcolor(BLUE);
	setcolor(WHITE);
	bar(0,0,640,45);
	bar(0,435,640,480);
	bar(0,0,45,480);
	bar(595,45,640,480);

	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(250,140,"MENU DE INICIO");
	outtextxy(260,170,"1. REGISTRO");
	outtextxy(260,200,"2. INICIAR SESION");
	outtextxy(260,230,"3. SAlIR");
	outtextxy(235,276,"SELECCIONE UNA OPCION: ");

	gotoxy(53,18); scanf("%d",&op);

	fflush(stdin);

	switch (op)
	{
        case 1:
            regist();
            break;
        case 2:
            login();
            break;
        case 3:
            exit(0);
		default:
			bar(200,300,440,320);
			setcolor(RED);
			outtextxy(225,308,"ERROR. Opcion no valida");
            getch();
			menuInicio();
            break;
    }
}

void regist(void)
{
	Usuario registro;
	char caracter;
	int i = 0;

	if (numusers == MAXUS)
	{
		setcolor(WHITE);
		bar(200,300,462,320);
		setcolor(RED);
		outtextxy(210,308,"Maximo de usuarios registrados!");
        getch();
		menuInicio();
    }

	cleardevice();

	setcolor(WHITE);
	bar(0,0,640,45);
	bar(0,435,640,480);

	outtextxy(250,140,"REGISTRO DE USUARIO");
	outtextxy(180,180,"Ingrese su nombre de usuario: ");
	outtextxy(180,228,"Ingrese su contrasena: ");

	gotoxy(53,12); scanf(" %[^\n]", registro.username);

	for (i = 0; i < numusers; i++)
	{
		if (strcmp(users[i].username, registro.username) == 0)
		{
			bar(145,300,500,320);
			setcolor(RED);
			outtextxy(150,308,"Ese nombre de usuario ya ha sido utilizado!!");
            getch();
            regist();
            return;
        }
    }

	gotoxy(46,15);

	while(1)
	{
		caracter = getch();

	    if (caracter == 13)
	    {
			registro.password[i]='\0';
			break;
		}

	    else if(caracter == 8)
	    {
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}

	    else
	    {
			if (i < LONG)
			{
				registro.password[i] = caracter;
				printf("%c",caracter);
				delay(100);
				printf("\b \b");
				printf("*");
				i++;
			}
	    }
	}

    strcpy(users[numusers].username, registro.username);
    strcpy(users[numusers].password, registro.password);
    numusers++;

	bar(200,300,448,320);
	setcolor(GREEN);
	outtextxy(206,308,"Usuario registrado con exito!!");
    getch();
	menuInicio();
}

void login(void)
{
    Usuario login;
	int i = 0, encontrado = 0;
	int intentos = 0;
	char caracter;

	if (numusers == 0)
	{
		bar(210,300,440,320);
		setcolor(RED);
		outtextxy(220,308,"Nadie se ha registrado aun!");
        getch();
		menuInicio();
	}

	cleardevice();
    bar(0,0,640,45);
	bar(0,435,640,480);

	do
	{
		cleardevice();
		bar(0,0,640,45);
		bar(0,435,640,480);

		outtextxy(250,140,"INICIO DE SESION");
		outtextxy(180,180,"Ingrese su nombre de usuario: ");
		outtextxy(180,228,"Ingrese su password: ");

		gotoxy(54,12);
		scanf(" %[^\n]", login.username);
		gotoxy(44,15);

		while(1)
		{
		   caracter = getch();

			if (caracter == 13)
			{
				login.password[i]='\0';
				break;
			}
			else if(caracter == 8)
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");
				}
			}
			else
			{
				if (i < LONG)
				{
					login.password[i] = caracter;
					printf("%c",caracter);
					delay(100);
					printf("\b \b");
					printf("*");
					i++;
				}
			}
		}

		for (i = 0; i < numusers; i++)
		{
            if (strcmp(users[i].username, login.username) == 0 &&
				strcmp(users[i].password, login.password) == 0){
                encontrado = 1;
                break;
            }
        }

		if (encontrado)
		{
			setcolor(WHITE);
			bar(215,300,415,320);
			setcolor(GREEN);
			outtextxy(255,308,"LOGIN EXITOSO!!");
            getch();
			menuPrincipal();
            return;
		}
		else
		{
            setcolor(WHITE);
			bar(215,300,428,320);
			setcolor(RED);
			outtextxy(225,308,"ERROR. Datos incorrectos.");
			setcolor(WHITE);
            getch();
            intentos++;
        }
	} while (intentos < 3);

    exit(0);
}

void menuPrincipal(void)
{
	int op;
	cleardevice();

	setbkcolor(BLACK);
	setcolor(WHITE);
	bar(0,0,640,45);
	bar(0,435,640,480);
    bar(0,0,45,480);
	bar(595,45,640,480);

	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(250,140,"MENU PRINCIPAL");
	outtextxy(260,170,"1. PRODUCTO");
	outtextxy(260,200,"2. CLIENTE");
	outtextxy(260,230,"3. SAlIR");
	outtextxy(235,276,"SELECCIONE UNA OPCION: ");

	gotoxy(53,18); scanf("%d",&op);

	fflush(stdin);

	switch (op)
	{
        case 1:
            menuInventario();
            break;
        case 2:
            menuCliente();
            break;
        case 3:
            exit(0);
		default:
			bar(200,300,440,320);
			setcolor(RED);
			outtextxy(225,308,"ERROR. Opcion no valida");
            getch();
            menuPrincipal();
            break;
    }
}

void menuInventario(void)
{
	char entrada[5];
	int opcion;
	int i;

	cleardevice();

	setcolor(WHITE);
	setfillstyle(1,WHITE);
	bar(0,0,640,20);
	bar(0,460,640,480);
	bar(0,0,20,480);
	bar(620,20,640,480);

	setbkcolor(MAGENTA);
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(250,100,"MENU PRODUCTO");
	outtextxy(260,140,"1. AGREGAR");
	outtextxy(260,170,"2. BUSCAR");
	outtextxy(260,200,"3. ACTUALIZAR");
	outtextxy(260,230,"4. ELIMINAR");
	outtextxy(260,260,"5. VER");
	outtextxy(260,290,"6. VENDER");
	outtextxy(260,320,"7. VOLVER");
	outtextxy(230,355,"SELECCIONE UNA OPCION: ");

	gotoxy(53,23); scanf(" %[^\n]",entrada);

	for(i = 0;i < strlen(entrada);i++)
	{
		if(isalpha(entrada[i]) || entrada[i] == ' ')
		{
        	setcolor(RED);
			outtextxy(240,380, "Opcion no valida!");
			getch();
			menuInventario();
		}
	}

	opcion = atoi(entrada);

	switch(opcion)
	{
		case 1:
			agregarProducto();
			break;
        case 2:
			buscarProducto();
            break;
		case 3:
			actualizarProducto();
			break;
		case 4:
			eliminarProducto();
			break;
		case 5:
			verProducto();
			break;
		case 6:
			venderProducto();
			break;
		case 7:
			menuPrincipal();
		default:
			setcolor(RED);
			outtextxy(240,380, "Opcion no valida!");
			getch();
			menuInventario();
	}
}

void agregarProducto(void)
{
	Producto new;
	int i,repetido = 0,invalido = 0,puntos;
	char cantidad[10],precio[10];

	cleardevice();

	setcolor(WHITE);
    setfillstyle(1,WHITE);
	bar(0,0,640,20);
	bar(0,460,640,480);

/* ------- Leer el codigo del producto y validacion ------- */
	do
	{
		taparProducto(356,94,635,111);
		setcolor(WHITE);

		outtextxy(250,60,"AGREGAR PRODUCTO");
		outtextxy(210,100,"Ingrese el codigo: ");
		gotoxy(46,7); scanf(" %s",new.codigo);

		for(i = 0;i < numproductos;i++)
		{
			if(strcmp(inventario[i].codigo,new.codigo) == 0)
			{
				taparProducto(356,94,635,111);

				setcolor(RED);
				outtextxy(368,103,"Codigo ya existente!");
				repetido = 1;
				getch();
			}
			else
			{
            	repetido = 0;
			}
		}

	} while(repetido == 1);

/* ------- Leer el nombre del producto y validacion ------- */
	do
	{
        repetido = 0;

		taparProducto(356, 126, 635, 143);

        setcolor(WHITE);
        outtextxy(210, 132, "Ingrese el nombre: ");
        gotoxy(46, 9);
		scanf(" %[^\n]", new.nombre);

		for(i = 0;i < strlen(new.nombre);i++)
		{
			new.nombre[i] = toupper(new.nombre[i]);
		}

		invalido = 0;

		for (i = 0; new.nombre[i] != '\0'; i++)
		{
			if (isdigit(new.nombre[i]) || !isalpha(new.nombre[i]))
			{
                invalido = 1;
                break;
            }
        }

		if (invalido)
		{
			taparProducto(356, 126, 635, 143);
            setcolor(RED);
			outtextxy(363, 132, "No ingrese numeros o simbolos");
            getch();
            continue;
        }

		for (i = 0; i < numproductos; i++)
		{
			if (strcmp(inventario[i].nombre, new.nombre) == 0 || strlen(new.nombre) > 19)
			{
				taparProducto(356, 126, 635, 143);
                setcolor(RED);
                outtextxy(368, 132, "Max 19 carac. y no repetido");
                repetido = 1;
                getch();
            }
        }

	} while (repetido == 1 || strlen(new.nombre) > 19 || invalido);

/* ------- Leer la cantidad de producto y validacion ------- */
	do
	{
		invalido = 0;
		taparProducto(370,159,635,175);
		setcolor(WHITE);
		outtextxy(210,164,"Ingrese la cantidad: ");
		gotoxy(48,11); scanf(" %[^\n]", cantidad);

		for(i = 0; cantidad[i] != '\0' ;i++)
		{
			if(!isdigit(cantidad[i]) || cantidad[i] == '.' || cantidad[i] == ',' || cantidad[i] == ' ')
			{
				invalido = 1;
				break;
			}
		}

		if(atoi(cantidad) <= 0)
		{
			invalido = 1;
		}

		if(invalido)
		{
			taparProducto(370,159,635,175);
			setcolor(RED);
			outtextxy(373,164,"Cantidad no valida!");
			setcolor(WHITE);
			getch();
		}

	} while(invalido);
    new.cantidad = atoi(cantidad);

/* ------- Leer el precio del producto y validacion ------- */
    do
	{
		invalido = 0;
		taparProducto(356,191,635,207);
		setcolor(WHITE);
		outtextxy(210,196,"Ingrese el precio: ");
		gotoxy(46,13);
		scanf(" %[^\n]", precio);

		puntos = 0;

		for (i = 0; precio[i] != '\0'; i++)
		{

			if (precio[i] == '.')
			{
				puntos++;

				if (puntos > 1)
				{
					invalido = 1;
					break;
				}
			}
			else if (!isdigit(precio[i]) || precio[i] == ' ')
			{
				invalido = 1;
				break;
			}
		}

		if(precio[strlen(precio) - 1] == '.' || precio[0] == '.')
		{
			invalido = 1;
		}
		else if(atof(precio) <= 0)
		{
			invalido = 1;
		}

		if (invalido)
		{
			taparProducto(356,191,635,207);
			setcolor(RED);
			outtextxy(359,196,"Precio no valido!");
			setcolor(WHITE);
			getch();
		}

	} while (invalido);
	new.precio = atof(precio);

/* ------- Leer la unidad de medida del producto ------- */
	outtextxy(210,228,"Ingrese la unidad de medida: ");
	gotoxy(56,15); scanf(" %s",new.unidad);

/* ------- Leer el vencimiento del producto, dia, mes, year + vali. ------- */
	outtextxy(250,260,"Vencimiento");

	do
	{
		invalido = 0;

		taparProducto(253,286,273,301);
		taparProducto(193,308,492,327);

		setcolor(WHITE);
		outtextxy(224,294,"Dia: ");
		gotoxy(33,19); scanf(" %s",&new.dia);

		for(i = 0;i < strlen(new.dia); i++)
		{
			if(!isdigit(new.dia[i]))
			{
				invalido = 1;
				break;
			}
		}

		if(strlen(new.dia) != 2 || invalido)
		{
			taparProducto(193,308,472,327);
			setcolor(RED);
			outtextxy(195,318,"Fecha no valida. Formato 00/00/0000");
			getch();
		}

		if(atoi(new.dia) > 31 || atoi(new.dia) < 1)
		{
			taparProducto(193,308,492,327);
			setcolor(RED);
			outtextxy(195,318,"Ese dia no existe. Ingrese uno valido");
			getch();
		}

	} while(strlen(new.dia) != 2 || atoi(new.dia) > 31 || atoi(new.dia) < 1 || invalido);

    do
	{
		invalido = 0;

		taparProducto(309,287,328,301);
		taparProducto(193,308,492,327);

		setcolor(WHITE);
        outtextxy(280,294,"Mes: ");
		gotoxy(40,19); scanf(" %s",&new.mes);

		for(i = 0;i < strlen(new.mes); i++)
		{
			if(!isdigit(new.mes[i]))
			{
				invalido = 1;
				break;
			}
		}

		if(atoi(new.dia) == 31 && (atoi(new.mes) == 2 || atoi(new.mes) == 4 ||
		   atoi(new.mes) == 6 || atoi(new.mes) == 9 || atoi(new.mes) == 11))
		{
			invalido = 1;
			break;
		}

		if(strlen(new.mes) != 2 || invalido)
		{
			taparProducto(193,308,472,327);
			setcolor(RED);
			outtextxy(195,318,"Fecha no valida. Formato 00/00/0000");
			getch();
		}

		if(atoi(new.mes) > 12 || atoi(new.mes) < 1)
		{
			taparProducto(193,308,492,327);
			setcolor(RED);
			outtextxy(195,318,"Ese mes no existe. Ingrese uno valido");
			getch();
		}

	} while(strlen(new.mes) != 2 || atoi(new.mes) > 12 || atoi(new.mes) < 1 || invalido);

    do
	{
		invalido = 0;

		taparProducto(373,284,636,303);
		taparProducto(193,308,492,327);

		setcolor(WHITE);
        outtextxy(336,294,"Year: ");
		gotoxy(48,19); scanf(" %s",&new.year);

		for(i = 0;i < strlen(new.year); i++)
		{
			if(!isdigit(new.year[i]))
			{
				invalido = 1;
				break;
			}
		}

		if(strlen(new.year) != 4 || invalido)
		{
			taparProducto(193,308,472,327);
			setcolor(RED);
			outtextxy(195,318,"Fecha no valida. Formato 00/00/0000");
			getch();
		}

		if(atoi(new.year) < 2025)
		{
			taparProducto(193,308,492,327);
			setcolor(RED);
			outtextxy(195,318,"Al menos debe vencer a partir de 2025");
			getch();
		}

	} while(strlen(new.year) != 4 || atoi(new.year) < 2025);

/* ------- Leer la descripcion del producto ------- */
	do
	{
		taparProducto(152,348,628,369);
		setcolor(WHITE);
		outtextxy(210,336,"Ingrese la descripcion: ");
		gotoxy(22,23); scanf(" %[^\n]",new.descripcion);

		if(strlen(new.descripcion) > 36)
		{
			taparProducto(152,348,628,369);
			setcolor(RED);
			outtextxy(212,359,"Max. 36 caracteres");
			getch();
		}

	} while(strlen(new.descripcion) > 36);

/* ------- Asignar los valores a la estructura inventario ------- */
	inventario[numproductos] = new;
	numproductos++;

	setfillstyle(1,WHITE);
	bar(190,416,450,436);
	setcolor(GREEN);
	outtextxy(205,424,"PRODUCTO AGREGADO CON EXITO!!");

	getch();
	menuInventario();
}

void buscarProducto(void)
{
	int i,index;
	char cantidad[10],precio[10];
	char referencia[LONG];

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menuInventario();
	}

	cleardevice();
	setcolor(WHITE);
	outtextxy(250,120,"BUSCAR PRODCUCTO");
	outtextxy(150,164,"Ingrese el codigo o nombre del producto: ");

	getchar(); gotoxy(60,11); gets(referencia);

	for(i = 0;i < strlen(referencia);i++)
	{
		referencia[i] = toupper(referencia[i]);
	}

	index = buscarPr(referencia);

	if (index != -1)
	{
		Producto pro = inventario[index];

		setcolor(WHITE);
		bar(0,190,639,290);
		setcolor(MAGENTA);
		rectangle(0,210,639,250);
		line(0,240,0,270);
		outtextxy(3,225,"Codigo");
		line(52,210,52,270);
		outtextxy(55,225,"Nombre");
		line(190,210,190,270);
		outtextxy(193,225,"Cant.");
		line(236,210,236,270);
		outtextxy(239,220,"Precio");
		outtextxy(247,230,"C$");
		line(290,210,290,270);
		outtextxy(310,225,"UM");
		line(344,210,344,270);
		outtextxy(347,225,"Vence");
		line(415,210,415,270);
		outtextxy(418,225,"Descripcion");
		line(639,210,639,270);

		line(0,270,639,270);

		outtextxy(5,255,pro.codigo);
		outtextxy(55,255,pro.nombre);

		sprintf(cantidad,"%d",pro.cantidad);
		outtextxy(193,255,cantidad);

		sprintf(precio,"%.1f",pro.precio);
		outtextxy(239,255,precio);

		outtextxy(293,255,pro.unidad);

		settextstyle(2,0,4);
		outtextxy(346,255,pro.dia);
		outtextxy(358,255,"/");
		outtextxy(365,255,pro.mes);
		outtextxy(377,255,"/");
		outtextxy(385,255,pro.year);
		outtextxy(418,255,pro.descripcion);

	}
	else
	{
		setcolor(WHITE);
		bar(223,200,413,220);
		setcolor(RED);
		outtextxy(228,208,"Producto no encontrado!");
	}
	getch();
	menuInventario();
}

void actualizarProducto(void)
{
	char referencia[LONG],cantidad[LONG],precio[LONG],entrada[LONG];
	int opcion,invalido;
	int i,idx;
	char continuar;

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menuInventario();
	}

	cleardevice();
	setcolor(WHITE);
	bar(0,0,640,20);

	outtextxy(250,60,"ACTUALIZAR PRODUCTO");
	outtextxy(50,116,"Ingrese el codigo o nombre del producto a actualizar: ");
	gotoxy(61,8); scanf(" %[^\n]",referencia);

    for(i = 0;i < strlen(referencia);i++)
	{
		referencia[i] = toupper(referencia[i]);
	}

	idx = buscarPr(referencia);

	if(idx == -1)
	{
    	setcolor(RED);
		outtextxy(230,140,"Producto no encontrado!");
		getch();
		menuInventario();
	}

	do
	{
		do
		{
			setcolor(MAGENTA);
			setfillstyle(1,MAGENTA);
			bar(0,130,640,480);
			setcolor(WHITE);
			outtextxy(100,150,"1.Codigo:");
			outtextxy(180,150,inventario[idx].codigo);
			outtextxy(100,170,"2.Nombre:");
			outtextxy(180,170,inventario[idx].nombre);
			outtextxy(100,190,"3.Cantidad:");

			sprintf(cantidad,"%d",inventario[idx].cantidad);
			outtextxy(192,190,cantidad);
			outtextxy(100,210,"4.Precio:");
			sprintf(precio,"%.1f",inventario[idx].precio);
			outtextxy(180,210,precio);
			outtextxy(100,230,"5.Unidad de medida:");
			outtextxy(260,230,inventario[idx].unidad);
			outtextxy(100,250,"6.Descripcion:");
			outtextxy(216,250,inventario[idx].descripcion);
			outtextxy(100,270,"7.Fecha de vencimiento:");
			outtextxy(292,270,inventario[idx].dia);
			outtextxy(308,270,"/");
			outtextxy(316,270,inventario[idx].mes);
			outtextxy(332,270,"/");
			outtextxy(340,270,inventario[idx].year);
			setcolor(YELLOW);
			outtextxy(100,292,"Seleccione el dato a actualizar:");
			gotoxy(46,19); scanf(" %[^\n]",entrada);

			invalido = 0;

			for (i = 0; i < strlen(entrada); i++)
			{
				if (!isdigit(entrada[i]) || entrada[i] == ' ')
				{
					invalido = 1;
            		break;
				}
			}

			if(atoi(entrada) > 7 || atoi(entrada) <= 0)
			{
				invalido = 1;
			}

			if (!invalido)
			{
				opcion = atoi(entrada);
			}
			else
			{
            	setcolor(RED);
        		outtextxy(100, 323, "Opcion no valida!");
        		getch();
			}

		} while (invalido);

		switch (opcion)
		{
			case 1:
				outtextxy(100,323,"Ingrese el nuevo codigo: ");
				gotoxy(38,21); scanf(" %s", inventario[idx].codigo);
				break;
			case 2:
				outtextxy(100,323,"Ingrese el nuevo nombre: ");
				gotoxy(38,21); scanf(" %s",inventario[idx].nombre);
				break;
			case 3:
				outtextxy(100,323,"Ingrese la nueva cantidad: ");
				gotoxy(41,21); scanf(" %d",&inventario[idx].cantidad);
				break;
			case 4:
				outtextxy(100,323,"Ingrese el nuevo precio: ");
				gotoxy(38,21); scanf(" %f", &inventario[idx].precio);
				break;
			case 5:
				outtextxy(100,323,"Ingrese la nueva unidad de medida: ");
				gotoxy(49,21); scanf(" %s",inventario[idx].unidad);
				break;
			case 6:
				outtextxy(100,323,"Nueva descripcion: ");
				gotoxy(32,21); scanf(" %[^\n]", inventario[idx].descripcion);
				break;
			case 7:
				outtextxy(100,323,"Nueva fecha de vencimiento: ");
				outtextxy(100,342,"Dia: ");
				gotoxy(18,22); scanf(" %s",inventario[idx].dia);

				outtextxy(156,342,"Mes: ");
				gotoxy(25,22); scanf(" %s",inventario[idx].mes);

				outtextxy(212,342,"Year: ");
				gotoxy(33,22);scanf(" %s",inventario[idx].year);
				break;
			default:
				setcolor(RED);
				outtextxy(100,323,"Opcion no valida!");
		}

		outtextxy(100,373,"Desea actualizar otro dato? (s/n): ");
		gotoxy(48,24); scanf(" %c", &continuar);

	} while (continuar == 's' || continuar == 'S');

	setfillstyle(1,WHITE);
	menuInventario();
}

void eliminarProducto(void)
{
	char continuar,afirmacion,referencia[50];
	int i,index;

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menuInventario();
	}

	cleardevice();

	setcolor(WHITE);
    bar(0,0,640,20);
	bar(0,460,640,480);

	outtextxy(250,120,"ELIMINAR PRODUCTO");
	outtextxy(100,164,"Ingrese el codigo o nombre del producto a eliminar: ");
	gotoxy(65,11); scanf("%s", referencia);

    for(i = 0;i < strlen(referencia);i++)
	{
		referencia[i] = toupper(referencia[i]);
	}


	index = buscarPr(referencia);

	if(index != -1)
	{
		setcolor(YELLOW);
		outtextxy(100,193,"Seguro que desea eliminar este producto?(s/n): ");
		gotoxy(60,13);
		scanf(" %c",&afirmacion);
	}
	else
	{
		setcolor(RED);
		outtextxy(228,208,"Producto no encontrado!");
		getch();
		menuInventario();
	}

	if(afirmacion == 's' || afirmacion == 'S')
	{
		if (index != -1)
		{
			for (i = index; i < numproductos - 1; i++)
			{
				inventario[i] = inventario[i + 1];
			}

			numproductos--;
			setcolor(WHITE);
			bar(233,220,413,240);
			setcolor(BLUE);
			outtextxy(249,228,"Producto eliminado!");
		}

		setcolor(YELLOW);
		outtextxy(150,260,"Desea eliminar otro producto?(s/n): ");
		gotoxy(55,17); scanf(" %c",&continuar);

		if(continuar == 's' || continuar == 'S')
		{
			eliminarProducto();
		}
		else
		{
			menuInventario();
		}
	}
	menuInventario();
}

void verProducto(void)
{
	int i, pagina = 0;
	char cantidad[10], precio[10];
	int Y;

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menuInventario();
	}

    cleardevice();

    setcolor(WHITE);
    setfillstyle(1, WHITE);
    bar(11, 11, 629, 50);
    setcolor(DARKGRAY);
    rectangle(10, 10, 630, 51);
    line(70, 10, 70, 50);
    line(154, 10, 154, 50);
    line(209, 10, 209, 50);
    line(266, 10, 266, 50);
    line(334, 10, 334, 50);
    line(424, 10, 424, 50);

    outtextxy(17, 27, "Codigo");
    outtextxy(77, 27, "Nombre");
    outtextxy(156, 27, "Cant.");
    outtextxy(212, 27, "Precio");
    outtextxy(272, 27, "Unidad");
    outtextxy(336, 27, "Fecha Venc.");
    outtextxy(428, 27, "Descripcion");

	do
	{
		for (i = pagina * 8; i < numproductos && i < (pagina + 1) * 8; i++)
		{
			Producto pro = inventario[i];
			Y = 50 + (i % 8) * 40;

			setcolor(DARKGRAY);
			rectangle(10, Y, 630, Y + 40);
			setcolor(WHITE);
			setfillstyle(1, WHITE);
			bar(11, Y + 1, 629, Y + 39);

			setcolor(DARKGRAY);
			line(70, Y, 70, Y + 40);
			line(154, Y, 154, Y + 40);
			line(209, Y, 209, Y + 40);
			line(266, Y, 266, Y + 40);
			line(334, Y, 334, Y + 40);
			line(424, Y, 424, Y + 40);

			settextstyle(2, 0, 4);
			outtextxy(17, Y + 18, pro.codigo);
			outtextxy(75, Y + 18, pro.nombre);

			sprintf(cantidad, "%d", pro.cantidad);
			outtextxy(160, Y + 18, cantidad);

			sprintf(precio, "%.1f", pro.precio);
			outtextxy(216, Y + 18, precio);

			outtextxy(276, Y + 18, pro.unidad);
			outtextxy(350, Y + 18, pro.dia);
			outtextxy(362, Y + 18, "/");
			outtextxy(369, Y + 18, pro.mes);
			outtextxy(381, Y + 18, "/");
			outtextxy(389, Y + 18, pro.year);
			outtextxy(428, Y + 18, pro.descripcion);
		}

	if ((pagina + 1) * 8 < numproductos)
	{
		setcolor(WHITE);
		settextstyle(0,0,1);
		outtextxy(60, Y + 100, "Presione cualquier boton para avanzar a la siguiente pagina...");
		getch();
		taparProducto(0,50,640,480);
    }

	pagina++;

	} while ((pagina - 1) * 8 < numproductos);

	getch();
	menuInventario();
}


void venderProducto(void)
{
	int i,index, indexcl, cant_vender, totalCompra, insuficiente, afirmacion = 0;
    char continuar, continuar2;
	char referencia[LONG], cantidad[10], precio[10], total[10],fact[10];

	if (numproductos == 0)
	{
        setcolor(RED);
        outtextxy(230, 380, "No hay ningun producto!");
        getch();
        menuInventario();
        return;
    }

	if (numclientes == 0)
	{
        setcolor(RED);
		outtextxy(230, 380, "No hay ningun cliente registrado!");
        getch();
        menuInventario();
        return;
    }

    cleardevice();
    setcolor(WHITE);
    outtextxy(250, 120, "VENDER PRODUCTO");
    outtextxy(150, 164, "Ingrese el codigo o nombre del producto: ");
    getchar();
    gotoxy(60, 11);
    gets(referencia);

    for (i = 0; i < strlen(referencia); i++)
	{
		referencia[i] = toupper(referencia[i]);
	}

    index = buscarPr(referencia);

	if (index != -1)
	{
        Producto pro = inventario[index];

		if (pro.cantidad == 0)
		{
            setcolor(RED);
            outtextxy(230, 330, "Producto no disponible!");
            getch();
            menuInventario();
            return;
		}

        setcolor(WHITE);
		bar(0,190,639,290);
		setcolor(MAGENTA);
		rectangle(0,210,639,250);
		line(0,240,0,270);
		outtextxy(3,225,"Codigo");
		line(52,210,52,270);
		outtextxy(55,225,"Nombre");
		line(190,210,190,270);
		outtextxy(193,225,"Cant.");
		line(236,210,236,270);
		outtextxy(239,220,"Precio");
		outtextxy(247,230,"C$");
		line(290,210,290,270);
		outtextxy(310,225,"UM");
		line(344,210,344,270);
		outtextxy(347,225,"Vence");
		line(415,210,415,270);
		outtextxy(418,225,"Descripcion");
		line(639,210,639,270);

		line(0,270,639,270);

		outtextxy(5,255,pro.codigo);
		outtextxy(55,255,pro.nombre);

		sprintf(cantidad,"%d",pro.cantidad);
		outtextxy(193,255,cantidad);

		sprintf(precio,"%.1f",pro.precio);
		outtextxy(239,255,precio);

		outtextxy(293,255,pro.unidad);

		settextstyle(2,0,4);
		outtextxy(346,255,pro.dia);
		outtextxy(358,255,"/");
		outtextxy(365,255,pro.mes);
		outtextxy(377,255,"/");
		outtextxy(385,255,pro.year);
		outtextxy(418,255,pro.descripcion);

		settextstyle(0,0,1);

		do
		{
			taparProducto(0, 320, 640, 480);
			taparProducto(459,300,640,321);
            setcolor(WHITE);
            outtextxy(150, 310, "Ingrese el codigo o correo del cliente: ");
            gotoxy(60, 20); scanf(" %[^\n]", referencia);

            indexcl = buscarCl(referencia);

			if (indexcl != -1)
			{
				if (clientes[indexcl].credito == 0)
				{
                    setcolor(RED);
                    outtextxy(120, 370, "El cliente no tiene creditos!");
                    getch();
                    menuInventario();
                    return;
                }

				do
				{
					taparProducto(0,350,640,480);
					taparProducto(443,331,640,350);
                    setcolor(WHITE);
                    outtextxy(150, 338, "Ingrese la cantidad que desea vender: ");
                    gotoxy(57, 22);
					scanf("%d", &cant_vender);

                    totalCompra = cant_vender * pro.precio;

                    insuficiente = 0;
					if (cant_vender > pro.cantidad)
					{
                        setcolor(RED);
                        outtextxy(150, 370, "Cantidad de producto insuficiente!");
                        insuficiente = 1;
					}
					else if (totalCompra > clientes[indexcl].credito)
					{
                        setcolor(RED);
						outtextxy(150, 370, "El cliente no tiene los creditos necesarios!");
                        insuficiente = 1;
                    }

					if (insuficiente)
					{
						setcolor(YELLOW);
						outtextxy(150, 390, "Desea seguir intentando? (s/n): ");
						gotoxy(51, 25); scanf(" %c", &continuar);

						if (continuar == 'n' || continuar == 'N')
						{
                            menuInventario();
                            return;
                        }
                    }
				} while (insuficiente);

				setcolor(YELLOW);
				outtextxy(150, 354, "El total es: C$ ");
				sprintf(total, "%d", totalCompra);
				outtextxy(278, 354, total);

				setcolor(YELLOW);
                outtextxy(150, 374, "Esta seguro de realizar la compra?(s/n): ");
                gotoxy(60, 24);
                scanf(" %c", &continuar2);

				if (continuar2 == 's' || continuar2 == 'S')
				{
                    inventario[index].cantidad -= cant_vender;
                    clientes[indexcl].credito -= totalCompra;

                    setcolor(GREEN);
                    outtextxy(196, 410, "COMPRA REALIZADA CON EXITO");
					getch();

					cleardevice();

					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(188,107,439,417);
					setcolor(BLACK);
					line(440,418,188,418);
					line(440,418,107,440);
					setcolor(BLACK);
					outtextxy(250,120,"FACTURA");
					numfactura++;
					sprintf(fact,"%d",numfactura);
					outtextxy(330,120,fact);

					outtextxy(200,150,"Cliente: ");
					outtextxy(272,150,clientes[indexcl].name);
					outtextxy(200,170,"Correo: ");
					outtextxy(272,170,clientes[indexcl].correo);
					outtextxy(200,190,"Codigo: ");
					outtextxy(272,190,clientes[indexcl].code);

					line(197,244,420,244);

					outtextxy(200,275,"Producto: ");
					outtextxy(280,275,inventario[index].nombre);

					outtextxy(200,295,"Cantidad: ");
					sprintf(cantidad,"%d",cant_vender);
					outtextxy(280,295,cantidad);

					outtextxy(200,315,"Precio: ");
					sprintf(precio,"%.2f",inventario[index].precio);
					outtextxy(272,315,precio);

					outtextxy(200,335,"Total: C$ ");
					sprintf(total,"%d",totalCompra);
					setcolor(GREEN);
					outtextxy(280,335,total);

					/*JERINGA*/
					setcolor(BLACK);
					line(407,401,424,401);
					line(415,401,415,390);
					rectangle(408,367,423,390);
					setcolor(GREEN);
					setfillstyle(1,GREEN);
					bar(409,368,422,389);
					setcolor(BLACK);
					rectangle(412,361,419,367);
					line(415,361,415,346);
					line(423,385,417,385);
					line(423,379,417,379);
					line(423,374,417,374);
					setcolor(WHITE);
					getch();
                    menuInventario();
                    return;
				}
				else
				{
                    setcolor(RED);
					outtextxy(200,410, "COMPRA CANCELADA");
                    getch();
                    menuInventario();
                    return;
                }
			}
			else
			{
                setcolor(RED);
                outtextxy(150, 330, "Cliente no encontrado, debe registrarlo!");
                setcolor(YELLOW);
				outtextxy(150, 355, "Desea seguir intentando con otro?(s/n): ");
				gotoxy(59,23); scanf(" %c", &continuar);

				if (continuar == 's' || continuar == 'S')
				{
                    afirmacion = 1;
				}
				else
				{
                    afirmacion = 0;
                    menuInventario();
                    return;
                }
            }
        } while (afirmacion);
	}
	else
	{
        setcolor(WHITE);
        bar(223, 200, 413, 220);
        setcolor(RED);
        outtextxy(228, 208, "Producto no encontrado!");
        getch();
        menuInventario();
    }
}

void menuCliente()
{
	char entrada[5];
	int opcion;
	int i;

	cleardevice();

	setcolor(WHITE);
	setfillstyle(1,WHITE);
	bar(0,0,640,20);
	bar(0,460,640,480);
	bar(0,0,20,480);
	bar(620,20,640,480);

	setbkcolor(LIGHTBLUE);
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(250,130,"MENU CLIENTE");
	outtextxy(260,170,"1. AGREGAR");
	outtextxy(260,200,"2. BUSCAR");
	outtextxy(260,230,"3. ACTUALIZAR");
	outtextxy(260,260,"4. ELIMINAR");
	outtextxy(260,290,"5. VER");
	outtextxy(260,320,"6. VOLVER");
	outtextxy(230,355,"SELECCIONE UNA OPCION: ");

	gotoxy(53,23); scanf(" %[^\n]",entrada);

	for(i = 0;i < strlen(entrada);i++)
	{
		if(isalpha(entrada[i]) || entrada[i] == ' ')
		{
        	setcolor(RED);
			outtextxy(240,380, "Opcion no valida!");
			getch();
			menuCliente();
		}
	}

	opcion = atoi(entrada);

	switch(opcion)
	{
		case 1:
			agregarCliente();
			break;
		case 2:
			buscarCliente();
            break;
		case 3:
			actualizarCliente();
			break;
		case 4:
			eliminarCliente();
			break;
		case 5:
			verCliente();
			break;
		case 6:
			menuPrincipal();
		default:
			setcolor(RED);
			outtextxy(240,380, "Opcion no valida!");
			getch();
			menuCliente();
	}
}

void agregarCliente(void)
{
	Cliente new;
	int i,repetido = 0,invalido = 0,len;

	cleardevice();

	setcolor(WHITE);
    setfillstyle(1,WHITE);
	bar(0,0,640,20);
	bar(0,460,640,480);

	do
	{
		taparCliente(356,94,635,111);
		setcolor(WHITE);

		outtextxy(250,60,"AGREGAR CLIENTE");
		outtextxy(210,100,"Ingrese el codigo: ");
		gotoxy(46,7);  scanf(" %s",new.code);

		for(i = 0;i < numclientes;i++)
		{
			if(strcmp(clientes[i].code,new.code) == 0)
			{
				taparCliente(356,94,635,111);

				setcolor(RED);
				outtextxy(368,103,"Codigo ya existente!");
				repetido = 1;
				getch();
			}
			else
			{
            	repetido = 0;
			}
		}

	} while(repetido);

  do {
        repetido = 0;

		taparCliente(356, 126, 635, 143);

        setcolor(WHITE);
        outtextxy(210, 132, "Ingrese el nombre: ");
		gotoxy(46,9); scanf(" %[^\n]",new.name);

		for(i = 0;i < strlen(new.name);i++)
		{
			new.name[i] = toupper(new.name[i]);
		}

		invalido = 0;

		for (i = 0; new.name[i] != '\0' && new.name[i] != '\n'; i++)
		{
			if (!isalpha(new.name[i]) && new.name[i] != ' ' || isdigit(new.name[i]))
			{
                invalido = 1;
                break;
            }
        }

		if (invalido)
		{
			taparCliente(356, 126, 635, 143);
            setcolor(RED);
			outtextxy(363, 132, "No ingrese numeros o simbolos");
            getch();
            continue;
        }

		for (i = 0; i < numclientes; i++)
		{
			if (strlen(new.name) > 19)
			{
				taparCliente(356, 126, 635, 143);
                setcolor(RED);
				outtextxy(368, 132, "Max 19 caracacteres");
                repetido = 1;
                getch();
            }
        }

	} while (strlen(new.name) > 19 || invalido);

	do
	{
		invalido = 0;
		taparCliente(450,159,635,175);
		setcolor(WHITE);
		outtextxy(210,164,"Ingrese su numero de telefono: ");
		gotoxy(58,11); scanf(" %s", new.telefono);

		for(i = 0; new.telefono[i] != '\0' ;i++)
		{
			if(!isdigit(new.telefono[i]) || strlen(new.telefono) != 8)
			{
				invalido = 1;
				break;
			}
		}

		if(invalido)
		{
			taparCliente(450,159,635,175);
			setcolor(RED);
			outtextxy(453,164,"Solo numeros y 8 dig.");
			setcolor(WHITE);
			getch();
		}

	} while(invalido);

	do
	{
		invalido = 0;
		taparCliente(344,188,635,209);
		setcolor(WHITE);
		outtextxy(210,196,"Ingrese su Gmail: ");
		gotoxy(45,13); scanf(" %[^\n]", new.correo);

		len = strlen(new.correo);

		for(i = 0; i < len;i++)
		{
			if(new.correo[i] == ' ')
			{
				taparCliente(344,188,635,209);
				setcolor(RED);
				outtextxy(350,199,"No contener espacios");
				setcolor(WHITE);
				invalido = 1;
				getch();
				break;
			}

			if(strcmp(new.correo,clientes[i].correo) == 0)
			{
				taparCliente(344,188,635,209);
				setcolor(RED);
				outtextxy(350,199,"Correo ya existente");
				setcolor(WHITE);
				invalido = 1;
				getch();
				break;
			}


		}
			if(!invalido && len >= 11)
			{
				if(strcmp(&new.correo[len - 10],"@gmail.com") != 0)
				{
					taparCliente(344,188,635,209);
					setcolor(RED);
					outtextxy(350,199,"[...]@gmail.com");
					setcolor(WHITE);
					invalido = 1;
					getch();
				}
			}
			else if(len < 11)
			{
				taparCliente(344,188,635,209);
				setcolor(RED);
				outtextxy(350,199,"Min 1 caract. + dominio de Gmail");
				setcolor(WHITE);
				invalido = 1;
				getch();
			}

	} while(invalido);

	do
	{
		taparCliente(161,237,635,300);
		setcolor(WHITE);
		outtextxy(210,228,"Ingrese su direccion: ");
		gotoxy(22,17); scanf(" %[^\n]",new.direccion);

		if(strlen(new.direccion) > 36)
		{
			taparCliente(161,237,635,300);
			setcolor(RED);
			outtextxy(215,244,"Max. 36 caracteres");
			getch();
		}

	} while(strlen(new.direccion) > 36);

	new.credito = 500.00;
	clientes[numclientes] = new;
	numclientes++;

	setfillstyle(1,WHITE);
	bar(190,416,450,436);
	setcolor(GREEN);
	outtextxy(205,424,"CLIENTE AGREGADO CON EXITO!!");

	getch();
	menuCliente();
}

void buscarCliente(void)
{
	int index;
	char referencia[LONG],cred[10];

	if(numclientes == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay clientes.");
		getch();
		menuCliente();
	}

	cleardevice();

	setcolor(WHITE);
	outtextxy(250,120,"BUSCAR CLIENTE");
	outtextxy(64,164,"Ingrese el codigo o correo del cliente a buscar: ");

	gotoxy(58,11); scanf(" %[^\n]",referencia);

	index = buscarCl(referencia);

	if (index != -1)
	{
		Cliente cl = clientes[index];

		setcolor(WHITE);
		bar(0,206,640,400);

		setcolor(LIGHTBLUE);
		outtextxy(250,220,"Codigo:");
		setcolor(MAGENTA);
		outtextxy(314,220,cl.code);

		setcolor(LIGHTBLUE);
		outtextxy(250,250,"Nombre:");
		setcolor(MAGENTA);
		outtextxy(314,250,cl.name);

		setcolor(LIGHTBLUE);
		outtextxy(250,280,"Telefono:");
		setcolor(MAGENTA);
		outtextxy(330,280,cl.telefono);

		setcolor(LIGHTBLUE);
		outtextxy(250,310,"Correo:");
		setcolor(MAGENTA);
		outtextxy(314,310,cl.correo);

		setcolor(LIGHTBLUE);
		outtextxy(190,340,"Direccion:");
		setcolor(MAGENTA);
		outtextxy(278,340,cl.direccion);

        setcolor(LIGHTBLUE);
		outtextxy(250,370,"Creditos: C$");
		setcolor(MAGENTA);
		sprintf(cred,"%.2f",clientes[index].credito);
		outtextxy(346,370,cred);

		setcolor(WHITE);
		outtextxy(150,440,"Presione cualquier tecla para continuar...");
	}
	else
	{
		setcolor(RED);
		outtextxy(228,208,"Cliente no encontrado!");
	}
	getch();
	menuCliente();
}

void actualizarCliente(void)
{
	char referencia[LONG],entrada[LONG],cred[10];
	int opcion,esnumerico;
	int i,idx;
	char continuar;
	float credito = 0.00;

	if(numclientes == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun cliente.");
		getch();
		menuCliente();
	}

	cleardevice();

	setcolor(WHITE);
	bar(0,0,640,20);

	outtextxy(250,60,"ACTUALIZAR CLIENTE");
	outtextxy(50,116,"Ingrese el codigo o correo del cliente: ");
	gotoxy(48,8);
	scanf(" %[^\n]",referencia);

	idx = buscarCl(referencia);

	if(idx == -1)
	{
		setcolor(RED);
			outtextxy(230,140,"Producto no encontrado!");
			getch();
			menuCliente();
	}

	do
	{
		do
		{
			setcolor(LIGHTBLUE);
			setfillstyle(1,LIGHTBLUE);
			bar(0,130,640,480);
			setcolor(WHITE);
			outtextxy(100,150,"1.Codigo:");
			outtextxy(180,150,clientes[idx].code);
			outtextxy(100,170,"2.Nombre:");
			outtextxy(180,170,clientes[idx].name);
			outtextxy(100,190,"3.Telefono:");
			outtextxy(192,190,clientes[idx].telefono);
			outtextxy(100,210,"4.Correo:");
			outtextxy(180,210,clientes[idx].correo);
			outtextxy(100,230,"5.Direccion:");
			outtextxy(210,230,clientes[idx].direccion);
			outtextxy(100,250,"6.Creditos: C$");
			sprintf(cred,"%.2f",clientes[idx].credito);
			outtextxy(242,250,cred);

			setcolor(YELLOW);
			outtextxy(100,274,"Seleccione el dato a actualizar:");
			gotoxy(46,18); scanf(" %[^\n]",entrada);


			esnumerico = 1;

			for (i = 0; i < strlen(entrada); i++)
			{
				if (!isdigit(entrada[i]))
				{
					esnumerico = 0;
            		break;
        		}
			}

			if (esnumerico)
			{
				opcion = atoi(entrada);
			}
			else
			{
				opcion = -1;
			}

			if (opcion < 0 || opcion > 6)
			{
				setcolor(RED);
				outtextxy(100, 282, "Opcion no valida!");
        		getch();
			}

		} while (opcion < 0 || opcion > 6);


		switch (opcion)
		{
			case 1:
				outtextxy(100,307,"Ingrese el nuevo codigo: ");
				gotoxy(38,20); scanf(" %s", clientes[idx].code);
				break;
			case 2:
				outtextxy(100,307,"Ingrese el nuevo nombre: ");
				gotoxy(38,20); scanf(" %[^\n]",clientes[idx].name);
				break;
			case 3:
				outtextxy(100,307,"Ingrese el nuevo telefono: ");
				gotoxy(41,20); scanf(" %s",clientes[idx].telefono);
				break;
			case 4:
				outtextxy(100,307,"Ingrese el nuevo correo: ");
				gotoxy(38,20); scanf(" %s", &clientes[idx].correo);
				break;
			case 5:
				outtextxy(100,307,"Ingrese la nueva direccion: ");
				gotoxy(49,20); scanf(" %[^\n]",clientes[idx].direccion);
				break;
			case 6:
				outtextxy(100,307,"Cuantos creditos va a sumar?: ");
				gotoxy(51,20); scanf(" %f",&credito);
				clientes[idx].credito += credito;
				break;
			default:
				setcolor(RED);
				outtextxy(100,323,"Opcion no valida!");
		}

		outtextxy(100,343,"Desea actualizar otro dato? (s/n): ");
		gotoxy(48,22);
		scanf(" %c", &continuar);

	} while (continuar == 's' || continuar == 'S');

	setfillstyle(1,WHITE);
	menuCliente();
}

void eliminarCliente(void)
{
	char continuar,afirmacion,referencia[50];
	int i,index;

	if(numclientes == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun cliente.");
		getch();
		menuCliente();
	}

	cleardevice();

	setcolor(WHITE);
    bar(0,0,640,20);
	bar(0,460,640,480);

	outtextxy(250,120,"ELIMINAR PRODUCTO");
	outtextxy(100,164,"Ingrese el codigo o correo del producto a eliminar: ");
	gotoxy(65,11);
	scanf("%s", referencia);

	index = buscarCl(referencia);

	if(index != -1)
	{
		setcolor(YELLOW);
		outtextxy(100,193,"Seguro que desea eliminar a este cliente?(s/n): ");
		gotoxy(61,13);
		scanf(" %c",&afirmacion);
	}
	else
	{
		setcolor(RED);
		outtextxy(228,208,"Cliente no encontrado!");
		getch();
		menuCliente();
	}

	if(afirmacion == 's' || afirmacion == 'S')
	{
		if (index != -1)
		{
			for (i = index; i < numclientes - 1; i++)
			{
				clientes[i] = clientes[i + 1];
			}
			numclientes--;
			setcolor(WHITE);
			bar(233,220,413,240);
			setcolor(BLUE);
			outtextxy(249,228,"Cliente eliminado!");
		}
		setcolor(YELLOW);
		outtextxy(150,260,"Desea eliminar a otro cliente?(s/n): ");
		gotoxy(56,17); scanf(" %c",&continuar);

		if(continuar == 's' || continuar == 'S')
		{
			eliminarCliente();
		}
		else
		{
			menuCliente();
		}
	}

	menuCliente();
}

void verCliente(void)
{
    int i, pagina = 0;
    char cred[10];
    int Y;

	if(numclientes == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun cliente!");
		getch();
		menuCliente();
	}
        cleardevice();

        setcolor(WHITE);
        setfillstyle(1, WHITE);
        bar(11, 11, 629, 50);
        setcolor(DARKGRAY);
        rectangle(10, 10, 630, 51);
        line(50, 10, 50, 50);
        line(162, 10, 162, 50);
        line(240, 10, 240, 50);
        line(374, 10, 374, 50);
        line(556, 10, 556, 50);

        outtextxy(17, 27, "Cod.");
        outtextxy(85, 27, "Nombre");
        outtextxy(166, 27, "Numero de");
        outtextxy(168, 36, "telefono");
        outtextxy(288, 27, "Gmail");
        outtextxy(434, 27, "Direccion");
        outtextxy(560, 27, "Creditos");

	do
	{
        for (i = pagina * 8; i < numclientes && i < (pagina + 1) * 8; i++)
        {
            Cliente cl = clientes[i];
            Y = 50 + (i % 8) * 40;

            setcolor(DARKGRAY);
            rectangle(10, Y, 630, Y + 40);
            setcolor(WHITE);
            setfillstyle(1, WHITE);
            bar(11, Y + 1, 629, Y + 39);

            setcolor(DARKGRAY);
            line(50, Y, 50, Y + 40);
            line(162, Y, 162, Y + 40);
            line(240, Y, 240, Y + 40);
            line(374, Y, 374, Y + 40);
            line(556, Y, 556, Y + 40);

            settextstyle(2, 0, 4);
            outtextxy(20, Y + 18, cl.code);
            outtextxy(52, Y + 18, cl.name);
            outtextxy(170, Y + 18, cl.telefono);
            outtextxy(242, Y + 18, cl.correo);
            outtextxy(376, Y + 18, cl.direccion);
            sprintf(cred, "%.2f", clientes[i].credito);
            setcolor(GREEN);
            outtextxy(562, Y + 18, "C$");
            outtextxy(582, Y + 18, cred);
        }

        if ((pagina + 1) * 8 < numclientes)
        {
            setcolor(WHITE);
            settextstyle(0, 0, 1);
			outtextxy(60, Y + 100, "Presione cualquier boton para avanzar a la siguiente pagina...");
            getch();
            taparCliente(0, 50, 640, 480);
        }

        pagina++;
    } while ((pagina - 1) * 8 < numclientes);

    getch();
    menuCliente();
}

int buscarPr(char *referencia)
{
	int i;
	for (i = 0; i < numproductos; i++) {
        if (strcmp(inventario[i].codigo, referencia) == 0 || strcmp(inventario[i].nombre, referencia) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarCl(char *referencia)
{
	int i;
	for (i = 0; i < numclientes; i++)
	{
		if (strcmp(clientes[i].code, referencia) == 0 ||
			strcmp(clientes[i].correo, referencia) == 0)
		{
            return i;
        }
    }
    return -1;
}

void taparProducto(int x, int y, int x2, int y2)
{
		setcolor(MAGENTA);
		setfillstyle(1,MAGENTA);
		bar(x,y,x2,y2);
}

void taparCliente(int x, int y, int x2, int y2)
{
		setcolor(LIGHTBLUE);
		setfillstyle(1,LIGHTBLUE);
		bar(x,y,x2,y2);
}

void inicio(void)
{
	int pantalla = DETECT,modo;
	initgraph(&pantalla,&modo," ");
	cleardevice();
}

void fin(void)
{
	getch();
	closegraph();
}