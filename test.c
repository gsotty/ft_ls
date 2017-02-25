/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:31:05 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/24 13:53:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>

#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>

#include <grp.h>

#include <pwd.h>

int		main(int argc, char **argv)
{
	int				total;
	time_t			t;
	char			*tm;
	int				fd;
	int				x;
	DIR				*dir;
	struct stat		buf;
	struct dirent	*result;
	struct group	*g;
	struct passwd	*p;

	total = 0;
	//result = malloc(sizeof(struct dirent) * 10);
	if (argc == 1)
	{
		if ((dir = opendir(".")) == NULL)
		{
			printf("error opendir\n");
			return (-1);
		}
		while ((result = readdir(dir)) != NULL)
		{
			// info result
		//	printf("nom du fichier = %s\n", result->d_name);
			/*
			printf("numero d'inoeud = %lld\n", result->d_ino);
			printf("longeur de cet enregistrement = %hu\n", result->d_reclen);
			printf("type du fichier = %hhu\n", result->d_type);
			// info stat
			printf("ID du périphérique contenant le fichier = %d\n",
					buf.st_dev);
			printf("numero d'inoeud = %lld\n", buf.st_ino);
			printf("protection = %hu\n", buf.st_mode);
			*/
			stat(result->d_name, &buf);
			if (S_ISREG(buf.st_mode) == 1)
				printf("-");
			if (S_ISDIR(buf.st_mode) == 1)
				printf("d");
			if (S_ISCHR(buf.st_mode) == 1)
				printf("c");
			if (S_ISBLK(buf.st_mode) == 1)
				printf("b");
			if (S_ISFIFO(buf.st_mode) == 1)
				printf("p");
			if (S_ISLNK(buf.st_mode) == 1)
				printf("l");
			if (S_ISSOCK(buf.st_mode) == 1)
				printf("s");
			if ((buf.st_mode & S_IRUSR) == S_IRUSR)
				printf("r");
			else
				printf("-");
			if ((buf.st_mode & S_IWUSR) == S_IWUSR)
				printf("w");
			else
				printf("-");
			if ((buf.st_mode & S_IXUSR) == S_IXUSR)
				printf("x");
			else
				printf("-");
			if ((buf.st_mode & S_IRGRP) == S_IRGRP)
				printf("r");
			else
				printf("-");
			if ((buf.st_mode & S_IWGRP) == S_IWGRP)
				printf("w");
			else
				printf("-");
			if ((buf.st_mode & S_IXGRP) == S_IXGRP)
				printf("x");
			else
				printf("-");
			if ((buf.st_mode & S_IROTH) == S_IROTH)
				printf("r");
			else
				printf("-");
			if ((buf.st_mode & S_IWOTH) == S_IWOTH)
				printf("w");
			else
				printf("-");
			if ((buf.st_mode & S_IXOTH) == S_IXOTH)
				printf("x");
			else
				printf("-");
			printf("\t");
			printf("%hd\t", buf.st_nlink);
			p = getpwuid(buf.st_uid);
			total += buf.st_nlink;
			printf("%s\t", p->pw_name);
			g = getgrgid(buf.st_gid);
			printf("%s\t", g->gr_name);
			printf("%lld\t", buf.st_size);
			tm = ctime(&buf.st_mtime);
			tm[16] = '\0';
			printf("%s\t", tm + 4);
			printf("%s\n", result->d_name);
			/*
			printf("Nb liens materiels = %hd\n", buf.st_nlink);
			printf("idantifiant de l'utilisateur = %d\n", buf.st_uid);
			printf("idantifiant du groupe l'utilisateur = %d\n", buf.st_gid);
			printf("taille totale en octets = %lld\n", buf.st_size);
			printf("taille de block pour E/S = %d\n", buf.st_blksize);
			printf("nombre de block alloues = %lld\n", buf.st_blocks);
			tm = ctime(&buf.st_atime);
			printf("heure dernier acces = %s", tm);
			tm = ctime(&buf.st_ctime);
			printf("heure dernier changement etat = %s", tm);
			tm = ctime(&buf.st_mtime);
			printf("heure dernier modification = %s", tm);
			// info groupe
			g = getgrgid(buf.st_gid);
			printf("nom du groupe = %s\n", g->gr_name);
			printf("nom de passe du groupe = %s\n", g->gr_passwd);
			printf("ID du groupe = %u\n", g->gr_gid);
			// info utilisateur
			p = getpwuid(buf.st_uid);
			printf("nom d'utilisateur = %s\n", p->pw_name);
			printf("nom de passe de l'utilisateur = %s\n", p->pw_passwd);
			printf("idantifiant de l'utilisateur = %d\n", p->pw_uid);
			printf("idantifiant du groupe l'utilisateur = %d\n", p->pw_gid);
			printf("nom reel = %s\n", p->pw_gecos);
			printf("repertoire personnel = %s\n", p->pw_dir);
			printf("interpreteur de commande = %s\n\n", p->pw_shell);
			*/
		}
		printf("total %d\n", total);
	}
	else if (argc >= 2)
	{
		x = 1;
		while (argv[x] != NULL)
		{
			printf("%s:\n", argv[x]);
			if ((dir = opendir(argv[x])) == NULL)
			{
				printf("error opendir\n");
				return (-1);
			}
			while ((result = readdir(dir)) != NULL)
			{
			// info result
			printf("nom du fichier = %s\n", result->d_name);
			/*
			printf("numero d'inoeud = %lld\n", result->d_ino);
			printf("longeur de cet enregistrement = %hu\n", result->d_reclen);
			printf("type du fichier = %hhu\n", result->d_type);
			// info stat
			printf("ID du périphérique contenant le fichier = %d\n",
					buf.st_dev);
			printf("numero d'inoeud = %lld\n", buf.st_ino);
			printf("protection = %hu\n", buf.st_mode);
			*/
			stat(result->d_name, &buf);
			if (S_ISREG(buf.st_mode) == 1)
				printf("-");
			if (S_ISDIR(buf.st_mode) == 1)
				printf("d");
			if (S_ISCHR(buf.st_mode) == 1)
				printf("c");
			if (S_ISBLK(buf.st_mode) == 1)
				printf("b");
			if (S_ISFIFO(buf.st_mode) == 1)
				printf("p");
			if (S_ISLNK(buf.st_mode) == 1)
				printf("l");
			if (S_ISSOCK(buf.st_mode) == 1)
				printf("s");
			if ((buf.st_mode & S_IRUSR) == S_IRUSR)
				printf("r");
			else
				printf("-");
			if ((buf.st_mode & S_IWUSR) == S_IWUSR)
				printf("w");
			else
				printf("-");
			if ((buf.st_mode & S_IXUSR) == S_IXUSR)
				printf("x");
			else
				printf("-");
			if ((buf.st_mode & S_IRGRP) == S_IRGRP)
				printf("r");
			else
				printf("-");
			if ((buf.st_mode & S_IWGRP) == S_IWGRP)
				printf("w");
			else
				printf("-");
			if ((buf.st_mode & S_IXGRP) == S_IXGRP)
				printf("x");
			else
				printf("-");
			if ((buf.st_mode & S_IROTH) == S_IROTH)
				printf("r");
			else
				printf("-");
			if ((buf.st_mode & S_IWOTH) == S_IWOTH)
				printf("w");
			else
				printf("-");
			if ((buf.st_mode & S_IXOTH) == S_IXOTH)
				printf("x");
			else
				printf("-");
			printf("\n");
			/*
			printf("Nb liens materiels = %hd\n", buf.st_nlink);
			printf("idantifiant de l'utilisateur = %d\n", buf.st_uid);
			printf("idantifiant du groupe l'utilisateur = %d\n", buf.st_gid);
			printf("taille totale en octets = %lld\n", buf.st_size);
			printf("taille de block pour E/S = %d\n", buf.st_blksize);
			printf("nombre de block alloues = %lld\n", buf.st_blocks);
			tm = ctime(&buf.st_atime);
			printf("heure dernier acces = %s", tm);
			tm = ctime(&buf.st_ctime);
			printf("heure dernier changement etat = %s", tm);
			tm = ctime(&buf.st_mtime);
			printf("heure dernier modification = %s", tm);
			// info groupe
			g = getgrgid(buf.st_gid);
			printf("nom du groupe = %s\n", g->gr_name);
			printf("nom de passe du groupe = %s\n", g->gr_passwd);
			printf("ID du groupe = %u\n", g->gr_gid);
			// info utilisateur
			p = getpwuid(buf.st_uid);
			printf("nom d'utilisateur = %s\n", p->pw_name);
			printf("nom de passe de l'utilisateur = %s\n", p->pw_passwd);
			printf("idantifiant de l'utilisateur = %d\n", p->pw_uid);
			printf("idantifiant du groupe l'utilisateur = %d\n", p->pw_gid);
			printf("nom reel = %s\n", p->pw_gecos);
			printf("repertoire personnel = %s\n", p->pw_dir);
			printf("interpreteur de commande = %s\n\n", p->pw_shell);
			*/
			}
			printf("\n");
			x++;
		}
	}
	else
	{
		printf("error argv\n");
		return (-1);
	}
	return (0);
}
