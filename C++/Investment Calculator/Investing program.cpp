
#include <iostream> 

using namespace std;
int main()

{ 
	int rerun = 1;

	while (rerun == 1) 
	{
		const int max = 100;
		double invest[max];
		double withdraw[max];

		double net = 0;
		double totalinvest = 0;
		double totalwithdrawn = 0;
		double currentinvest;

		double count1 = 0;
		double count2 = 0;

		cout << "Investing Program" << endl << endl;

		//ENTER MONEY INVESTED
		for (int i = 0; i < max; i++)
		{
			cout << i + 1 << ". Enter money invested (enter 0 to stop): $";
			cin >> invest[i];

			if (invest[i] == 0)
			{
				i = 100;
			}
			else
			{
				count1++;
			}
		}

		//ADD ALL INVEST
		for (int k = 0; k < count1; k++)
		{
			totalinvest = totalinvest + invest[k];
		}

		//PRINT
		cout << endl;
		cout << "Total Money Invested: $" << totalinvest << endl;
		cout << endl;

		//ENTER MONEY WITHDRAWN
		for (int b = 0; b < max; b++)
		{
			cout << b + 1 << ". Enter money withdrawn (enter 0 to stop): $";
			cin >> withdraw[b];

			if (withdraw[b] == 0)
			{
				b = 100;
			}
			else
			{
				count2++;
			}
		}

		//ADD ALL WITHDRAWN
		for (int x = 0; x < count2; x++)
		{
			totalwithdrawn = totalwithdrawn + withdraw[x];
		}

		//PRINT
		cout << endl;
		cout << "Total Money Withdrawn: $" << totalwithdrawn << endl;
		cout << endl;

		//PRINT
		cout << endl << "Enter the value your current investment is worth: $" ;
		cin >> currentinvest;


		//CALCULATE NET GAIN/LOSS
		net = (totalwithdrawn + currentinvest)- totalinvest;

		//PRINT
		cout << endl << endl << "Net Gain/Loss (+ = gain, - = loss): $" << net << endl;

		cout << endl << "Enter 1 - Rerun" << endl << "Enter 0 - Exit" << endl << "Enter here:";
		cin >> rerun;

	}
	return 0;
}