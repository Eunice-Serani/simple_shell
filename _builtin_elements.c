#include "my_shell"
/**
 * m_xit - exit the custom shell.
 * @i: Structure with potential args.
 *
 * Return: Exits with given status (0) if i->argv[0] != "exit".
 */
int m_xit(info_t *i)
{
	int xst;

	if (i->argv[1])
	{
		xst = catoi(i->argv[1]);
		if (xst == -1)
		{
			i->status = 2;
			cerr("Illegal number: ");
			cputs(i->argv[1]);
			cput('\n');
			return (1);
		}
		i->err_num = catoi(i->argv[1]);
		return (-2);
	}
	i->err_num = -1;
	return (-2);
}

/**
 * m_cd - Change the current dir of the process.
 * @i: Structure with potential args.
 *
 * Return: Always 0.
 */
int m_cd(info_t *i)
{
	char *c, *d, b[1024];
	int r;

	c = getcwd(b, 1024);
	if (!c)
	{
		cputs("TODO: >>getcwd failure emsg here<<\n");
	}
	if (!i->argv[1])
	{
		d = cgetenv(i, "HOME=");
		if (!d)
		{
			r = chdir((d = cgetenv(i, "PWD=")) ? d : "/");
		}
		else
		{
			r = chdir(d);
		}
	}
	else if (cstrcmp(i->argv[1], "-") == 0)
	{
		if (!cgetenv(i, "OLDPWD="))
		{
			cputs(c);
			cput('\n');
			return (1);
		}
		cputs(cgetenv(i, "OLDPWD="));
		cput('\n');
		r = chdir((d = cgetenv(i, "OLDPWD=")) ? d : "/");
	}
	else
	{
		r = chdir(i->argv[1]);
	}
	if (r == -1)
	{
		cerr("Can't change dir to ");
		ceputs(i->argv[1]);
		ceput('\n');
	}
	else
	{
		csetenv(i, "OLDPWD", cgetenv(i, "PWD="));
		csetenv(i, "PWD", getcwd(b, 1024));
	}
	return (0);
}

/**
 * m_hlp - Display help message.
 * @i: Structure with potential args.
 *
 * Return: Always 0.
 */
int m_hlp(info_t *i)
{
	char **a;

	a = i->argv;
	cputs("Help call works. Function not yet implemented \n");
	if (0)
	{
		cputs(*a); /* Temp att_unused workaround */
	}
	return (0);
}

