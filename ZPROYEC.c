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

typedef struct {
    char username[LONG];
    char password[LONG];
} Usuario;

Usuario users[MAXUS];
int numusers = 0;

typedef struct{
	char codigo[4];
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

void inicio(void);
void fin(void);
void menu(void);
void regist(void);
void login(void);
void menu2(void);
void agregar(void);
void buscar(void);
void actualizar(void);
void eliminar(void);
void ver(void);
void tapar(int x, int y, int x2, int y2);
int buscarProducto(char *referencia);

int main(void)
{
	inicio();
	menu();
	fin();

    return 0;
}

void menu(void)
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

	gotoxy(53,18);
	scanf("%d",&op);

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
            menu();
            break;
    }
}

void regist(void)
{
    Usuario registro;
	int i;

	if (numusers == MAXUS)
	{
		setcolor(WHITE);
		bar(200,300,462,320);
		setcolor(RED);
		outtextxy(210,308,"Maximo de usuarios registrados!");
        getch();
        menu();
    }

	cleardevice();

	setcolor(WHITE);
	bar(0,0,640,45);
	bar(0,435,640,480);


	outtextxy(250,140,"REGISTRO DE USUARIO");
	outtextxy(180,180,"Ingrese su nombre de usuario: ");
	outtextxy(180,228,"Ingrese su contrasena: ");

	gotoxy(53,12);
	scanf(" %[^\n]", registro.username);

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
	scanf(" %[^\n]", registro.password);

    strcpy(users[numusers].username, registro.username);
    strcpy(users[numusers].password, registro.password);
    numusers++;

	bar(200,300,448,320);
	setcolor(GREEN);
	outtextxy(206,308,"Usuario registrado con exito!!");
    getch();
    menu();
}

void login(void)
{
    Usuario login;
    int i, encontrado = 0;
	int intentos = 0;

	if (numusers == 0)
	{
		bar(210,300,440,320);
		setcolor(RED);
		outtextxy(220,308,"Nadie se ha registrado aun!");
        getch();
        menu();
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
		scanf(" %[^\n]", login.password);

        for (i = 0; i < numusers; i++) {
            if (strcmp(users[i].username, login.username) == 0 &&
                strcmp(users[i].password, login.password) == 0) {
                encontrado = 1;
                break;
            }
        }

		if (encontrado) {
			setcolor(WHITE);
			bar(215,300,415,320);
			setcolor(GREEN);
			outtextxy(255,308,"LOGIN EXITOSO!!");
            getch();
			menu2();
            return;
		} else {
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

void menu2(void)
{
	int op;

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
	outtextxy(250,130,"MENU PRINCIPAL");
	outtextxy(260,170,"1. AGREGAR");
	outtextxy(260,200,"2. BUSCAR");
	outtextxy(260,230,"3. ACTUALIZAR");
	outtextxy(260,260,"4. ELIMINAR");
	outtextxy(260,290,"5. VER");
	outtextxy(260,320,"6. VOLVER");
	outtextxy(230,355,"SELECCIONE UNA OPCION: ");

	gotoxy(53,23);

	scanf("%d",&op);

	switch(op)
	{
		case 1:
			agregar();
			break;
        case 2:
            buscar();
            break;
		case 3:
			actualizar();
			break;
		case 4:
			eliminar();
			break;
		case 5:
			ver();
			break;
		case 6:
			exit(0);
		default:
			printf("INVALIDO");
	}
}

void agregar(void)
{
	Producto new;
	int i,repetido = 0,invalido = 0,puntos;
	char cantidad[10],precio[10];

	cleardevice();

	setcolor(WHITE);
    setfillstyle(1,WHITE);
	bar(0,0,640,20);
	bar(0,460,640,480);

	do
	{
		tapar(356,94,635,111);
		setcolor(WHITE);

		outtextxy(250,60,"AGREGAR PRODUCTO");
		outtextxy(210,100,"Ingrese el codigo: ");
		gotoxy(46,7); scanf(" %s",new.codigo);

		for(i = 0;i < numproductos;i++)
		{
			if(strcmp(inventario[i].codigo,new.codigo) == 0)
			{
				tapar(356,94,635,111);

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

	do
	{
		repetido = 0;

		tapar(356,126,635,143);

		setcolor(WHITE);
		outtextxy(210,132,"Ingrese el nombre: ");
		gotoxy(46,9); scanf(" %[^\n]",new.nombre);

		for(i = 0;i < numproductos;i++)
		{
			if(strcmp(inventario[i].nombre,new.nombre) == 0 || strlen(new.nombre) > 19)
				{
					tapar(356,126,635,143);

					setcolor(RED);
					outtextxy(368,132,"Max 19 carac. y no repetido");
					repetido = 1;
					getch();
				}
		}

	} while(repetido == 1 || strlen(new.nombre) > 19);

	do
	{
		invalido = 0;
		tapar(370,159,635,175);
		setcolor(WHITE);
		outtextxy(210,164,"Ingrese la cantidad: ");
		gotoxy(48,11); scanf(" %s", cantidad);

		for(i = 0; cantidad[i] != '\0' ;i++)
		{
			if(!isdigit(cantidad[i]) || cantidad[i] == '.' || cantidad[i] == ',')
			{
				invalido = 1;
				break;
			}
		}

		if(invalido)
		{
            tapar(370,159,635,175);
			setcolor(RED);
			outtextxy(373,164,"Cantidad no valida!");
			setcolor(WHITE);
			getch();
		}

	} while(invalido);
    new.cantidad = atoi(cantidad);

    do
	{
		invalido = 0;
		tapar(356,191,635,207);
		setcolor(WHITE);
		outtextxy(210,196,"Ingrese el precio: ");
		gotoxy(46,13);
		scanf(" %s", precio);

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
			else if (!isdigit(precio[i]) )
			{
				invalido = 1;
				break;
			}
		}

		if(precio[strlen(precio) - 1] == '.' || precio[0] == '.')
		{
			invalido = 1;
		}

		if (invalido)
		{
			tapar(356,191,635,207);
			setcolor(RED);
			outtextxy(359,196,"Precio no valido!");
			setcolor(WHITE);
			getch();
		}

	} while (invalido);
	new.precio = atof(precio);

	outtextxy(210,228,"Ingrese la unidad de medida: ");
	gotoxy(56,15); scanf(" %s",new.unidad);

	outtextxy(250,260,"Vencimiento");

	outtextxy(224,294,"Dia: ");
	gotoxy(33,19); scanf(" %s",&new.dia);

	outtextxy(280,294,"Mes: ");
	gotoxy(40,19); scanf(" %s",&new.mes);

	outtextxy(336,294,"Year: ");
	gotoxy(48,19); scanf(" %s",&new.year);

	outtextxy(210,336,"Ingrese la descripcion: ");
	gotoxy(22,23); scanf(" %[^\n]",new.descripcion);

	inventario[numproductos] = new;
	numproductos++;

	bar(190,416,450,436);
	setcolor(GREEN);
	outtextxy(205,424,"PRODUCTO AGREGADO CON EXITO!!");

	getch();
	menu2();
}

void buscar()
{
	int index;
	char cantidad[10],precio[10];
	char referencia[LONG];

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menu2();
	}

	cleardevice();
	setcolor(WHITE);
	outtextxy(250,120,"BUSCAR PRODCUCTO");
	outtextxy(150,164,"Ingrese el codigo o nombre del producto: ");

	getchar();
	gotoxy(60,11);
	gets(referencia);

	index = buscarProducto(referencia);

	if (index != -1)
	{
		Producto pro = inventario[index];

		setcolor(WHITE);
		bar(0,190,639,290);
		setcolor(LIGHTBLUE);
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
	menu2();
}

int buscarProducto(char *referencia)
{
	int i;
	for (i = 0; i < numproductos; i++) {
        if (strcmp(inventario[i].codigo, referencia) == 0 || strcmp(inventario[i].nombre, referencia) == 0) {
            return i;
        }
    }
    return -1;
}

void ver(void)
{
	int i = 0;
    char cantidad[10],precio[10];
	int Y = 50 + (i * 40);

	cleardevice();

	if (numproductos == 0)
	{
        printf("No hay productos en el inventario.\n");
        return;
	}

 	setcolor(WHITE);
		setfillstyle(1,WHITE);
		bar(11,11,629,50);
		setcolor(DARKGRAY);
		rectangle(10,10,630,51);
		line(70,10,70,50);
		line(154,10,154,50);
		line(209,10,209,50);
		line(266,10,266,50);
		line(334,10,334,50);
		line(424,10,424,50);

		outtextxy(17,27,"Codigo");
		outtextxy(77,27,"Nombre");
		outtextxy(156,27,"Cant.");
		outtextxy(212,27,"Precio");
		outtextxy(272,27,"Unidad");
		outtextxy(336,27,"Fecha Venc.");
		outtextxy(428,27,"Descripcion");


	 for (i = 0; i < numproductos; i++) {
        Producto pro = inventario[i];
        Y = 50 + i * 40;

        rectangle(10, Y, 630, Y + 40);
        setcolor(WHITE);
        setfillstyle(1, WHITE);
        bar(11, Y + 1, 629, Y + 39);

        setcolor(DARKGRAY);
		line(70,Y,70,Y+40);
		line(154,Y,154,Y+40);
		line(209,Y,209,Y+40);
		line(266,Y,266,Y+40);
		line(334,Y,334,Y+40);
		line(424,Y,424,Y+40);

        settextstyle(2, 0, 4);
        outtextxy(17, Y + 18, pro.codigo);
		outtextxy(75, Y + 18, pro.nombre);

        sprintf(cantidad, "%d", pro.cantidad);
		outtextxy(160, Y + 18, cantidad);

        sprintf(precio, "%.1f", pro.precio);
		outtextxy(216, Y + 18, precio);

		outtextxy(276, Y + 18, pro.unidad);

		outtextxy(350,Y + 18,pro.dia);
		outtextxy(362,Y + 18,"/");
		outtextxy(369,Y + 18,pro.mes);
		outtextxy(381,Y + 18,"/");
		outtextxy(389,Y + 18,pro.year);

		outtextxy(428, Y + 18, pro.descripcion);
    }
   getch();
   menu2();
}

void actualizar(void)
{
	char referencia[LONG],cantidad[LONG],precio[LONG],entrada[LONG];
    int encontrado = 0;
	int opcion,esnumerico;
	int i,idx;
	char continuar;

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menu2();
	}

	cleardevice();
	setcolor(WHITE);
	bar(0,0,640,20);

	outtextxy(250,60,"ACTUALIZAR PRODUCTO");
	outtextxy(50,116,"Ingrese el codigo o nombre del producto a actualizar: ");
	gotoxy(61,8);
	scanf("%s",referencia);

	   for (i = 0; i < numproductos; i++)
		{
			if (strcmp(inventario[i].codigo, referencia) == 0 ||
				strcmp(inventario[i].nombre, referencia) == 0)
			{
				encontrado = 1;
				idx = i;
			}
		}

	   if (!encontrado)
	   {
		setcolor(RED);
			outtextxy(230,140,"Producto no encontrado!");
			getch();
			menu2();
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
			gotoxy(46,19);
			scanf("%s",entrada);


    			esnumerico = 1;
				for (i = 0; i < strlen(entrada); i++) {
        		if (!isdigit(entrada[i])) {
					esnumerico = 0;
            		break;
        		}
    			}

    			if (esnumerico) {
					opcion = atoi(entrada);
    			} else {
					opcion = -1;
    			}

				if (opcion < 0 || opcion > 7)
				{
        		setcolor(RED);
        		outtextxy(100, 323, "Opcion no valida!");
        		getch();
    			}

			} while (opcion < 0 || opcion > 7);


			switch (opcion)
			{
				case 1:
						outtextxy(100,323,"Ingrese el nuevo codigo: ");
						gotoxy(38,21);
						scanf("%s", inventario[idx].codigo);
                        break;
                    case 2:
						outtextxy(100,323,"Ingrese el nuevo nombre: ");
						gotoxy(38,21);
						scanf("%s",inventario[idx].nombre);
                        break;
                    case 3:
						outtextxy(100,323,"Ingrese la nueva cantidad: ");
						gotoxy(41,21);
						scanf("%d",&inventario[idx].cantidad);
                        break;
                    case 4:
						outtextxy(100,323,"Ingrese el nuevo precio: ");
						gotoxy(38,21);
						scanf("%f", &inventario[idx].precio);
                        break;
                    case 5:
						outtextxy(100,323,"Ingrese la nueva unidad de medida: ");
						gotoxy(49,21);
						scanf("%s",inventario[idx].unidad);
                        break;
                    case 6:
						outtextxy(100,323,"Nueva descripcion: ");
						gotoxy(32,21);
						scanf(" %[^\n]", inventario[idx].descripcion);
                        break;
					case 7:
						outtextxy(100,323,"Nueva fecha de vencimiento: ");
						outtextxy(100,342,"Dia: ");
						gotoxy(18,22);
						scanf("%s",inventario[idx].dia);

						outtextxy(156,342,"Mes: ");
						gotoxy(25,22);
						scanf("%s",inventario[idx].mes);

						outtextxy(212,342,"Year: ");
						gotoxy(33,22);
						scanf("%s",inventario[idx].year);
                        break;
					default:
						setcolor(RED);
						outtextxy(100,323,"Opcion no valida!");
                }

				outtextxy(100,373,"Desea actualizar otro dato? (s/n): ");
				gotoxy(48,24);
				scanf(" %c", &continuar);

		} while (continuar == 's' || continuar == 'S');

	setfillstyle(1,WHITE);
	menu2();
}

void eliminar(void)
{
	char continuar,afirmacion,referencia[50];
	int i,index;

	if(numproductos == 0)
	{
		setcolor(RED);
		outtextxy(230,380,"No hay ningun producto!");
		getch();
		menu2();
	}

	cleardevice();

	setcolor(WHITE);
    bar(0,0,640,20);
	bar(0,460,640,480);

	outtextxy(250,120,"ELIMINAR PRODUCTO");
	outtextxy(100,164,"Ingrese el codigo o nombre del producto a eliminar: ");
	gotoxy(65,11);
	scanf("%s", referencia);


	index = buscarProducto(referencia);

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
		menu2();
	}

	if(afirmacion == 's' || afirmacion == 'S')
	{
    if (index != -1)
	{
		for (i = index; i < numproductos - 1; i++) {
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
	gotoxy(55,17);
	scanf(" %c",&continuar);

	if(continuar == 's' || continuar == 'S')
	{
		eliminar();
	}
	else
	{
		menu2();
	}
	}

	menu2();
}

void tapar(int x, int y, int x2, int y2)
{
		setcolor(LIGHTBLUE);
		setfillstyle(1,LIGHTBLUE);
		bar(x,y,x2,y2);
}


void inicio(void)
{
	int pantalla = DETECT,modo;
	initgraph(&pantalla,&modo," ");
}

void fin(void)
{
	cleardevice();
	closegraph();
	exit(0);
}