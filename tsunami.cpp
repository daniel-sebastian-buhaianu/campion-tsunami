#include <fstream>

#define NRD 4 // numar directii (nord, est, sud, vest)

using namespace std;

ifstream fin("tsunami.in");
ofstream fout("tsunami.out");

struct zona { int l, c; };

int main()
{
	int n, m, h, i, j, vf, k, nrz;

	// initializez vectori ajutatori de directie
	// dl = directie linie
	// dc = directie coloana
	// a[i + dl[k]][j + dc[k]] = al k-lea vecin al lui a[i][j]
	int dl[] = {-1, 0, 1, 0};
	int dc[] = {0, 1, 0, -1};

	fin >> n >> m >> h;
	
	int a[n+2][m+2];

	// initializez stiva
	zona stv[n*m];
	vf = -1;
	
	// citesc elementele din matricea a

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			fin >> a[i][j];

			// adaug in stiva zonele cu apa

			if (a[i][j] == 0)
			{
				stv[++vf].l = i;
				stv[vf].c = j;
			}
		}
	}

	fin.close();

	// bordez matricea
	
	for (i = 0; i <= m+1; i++)
	{
		a[0][i] = a[n+1][i] = -1;
	}

	for (i = 0; i <= n+1; i++)
	{
		a[i][0] = a[i][m+1] = -1;
	}

	// identific zonele afectate de tsunami

	while (vf >= 0)
	{
		zona z = stv[vf--];

		for (k = 0; k < NRD; k++)
		{
			i = z.l + dl[k];
			j = z.c + dc[k];

			if (a[i][j] > 0 && a[i][j] < h)
			{
				a[i][j] *= -1;

				stv[++vf].l = i;
				stv[vf].c = j;
			}
		}
	}
	
	// calculez nr. de zone afectate de tsunami
	nrz = 0;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (a[i][j] < 0)
			{
				nrz++;
			}
		}
	}

	fout << nrz;

	fout.close();

	return 0;
}

// scor 100
