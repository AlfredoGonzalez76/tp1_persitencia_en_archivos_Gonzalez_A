#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import time  
import os
def agenda():      #Este programa sirve para agregar,modificar,eliminar y consultar contactos de una agenda
	contactos = {}
	salir=True
	while(salir):

		print('Bienvenido A Mi Agenda\n')
		print(' 1.) Ver Contactos\n 2.) Agregar Contacto\n 3.) Buscar Contacto\n 4.) Modificar Contacto\n 5.) Eliminar Contacto\n 6.) Salir\n')
		
		opcion=input('Digite el numero de la opcion que desea ver: ')
		os.system('clear')
		if opcion == '1': # <----Muestra los contactos
			for contacto in contactos:
				for numero in contactos:
					print('Contacto / Numero')
					print( numero,contactos[contacto])
				
			time.sleep(4)
			os.system('clear')

		elif opcion == '2': # <----Registra los contactos
			nombre=input('Nombre: ')
			if nombre in contactos:
				print('Error el contacto ya existe')
				time.sleep(3)
				os.system('clear')
				continue
			try:
				numero=int(input('Numero: '))
				if numero>9999999999:
					print('El numero es demaciado largo')
					time.sleep(3)
					os.system('clear')
					continue
				elif numero<1000000000:
					print('El numero es demaciado corto\nDeben de ser 10 digistos')
					time.sleep(2)
					os.system('clear')
					continue
				
			except:
				print('Valor no valido')
				time.sleep(3)
				os.system('clear')
			contactos[(nombre)] = numero
			print('Contacto agregado')
			print(contactos)
			time.sleep(3)
			os.system('clear')

		elif opcion == '3': # <----- Buscar Contacto
			buscar=input('Contacto a Buscar: ')
			print (contactos[buscar])
			time.sleep(3)
			os.system('clear')
			if buscar not in contactos:
				print('El contacto no existe., agreguelo desde el menu')
				continue

		elif opcion == '4': # <------- Modificar contacto
			contacto = input('Contacto a modificar: ')
			if contacto not in contactos:
				print ('El contacto no existe, agreguelo desde el menu')
				continue
			try:
				nuevo=int(input('Nuevo Numero: '))
				contactos[contacto]=nuevo
				if numero>9999999999:
					print('El numero es de maciado largo')
					time.sleep(3)
					os.system('clear')
					continue
				elif numero<1000000000:
					print('El numero es muy corto\nDeben de ser 10 digitos')
				print('Contacto modificado con exito')
				time.sleep(3)
				os.system('clear')
				continue
			except:
				print('¡Dato no valido!')
				time.sleep(3)
				os.system('clear')
				continue

		elif opcion == '5':
			eliminar=input('Contacto a eliminar: ')
			if eliminar not in contactos:
				print ("El contacto no existe")
				continue
			del(contactos[eliminar])
			print('Contacto',eliminar,'eliminado con exito')
			time.sleep(4)
			os.system('clear')
			continue
		elif opcion == '6': # <---- regresar al menu principal
			os.system('exit')
		else:
			print('Opcion no valida,\nElija una opcion del 1 al 6')
			time.sleep(3)
			os.system('clear')
agenda()


# In[ ]:




