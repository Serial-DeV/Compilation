void main()
{
	int k = 15;
	int l = 15;
	int n = 12;
	int o = 65;
	int p = 43;

	if(k > 2*o)
	{
		int k = 10;
		print("test 1 vrai\n");
		print(k);	
	}
	
	else
	{
		print("test 1 faux\n");
	}
	
	if(k < 12+1)
	{
		int o = 50;
		print("test 2 vrai\n");
		print(o);
	}
	
	else
	{
		print("test 2 faux\n");
	}

	if(k >= l)
	{
		int l = 67;
		k = 14;
		print("test 3 vrai\n");
		print(l);	
	}
	
	else
	{
		print("test 3 faux\n");
	}
	
	if(k <= 14)
	{
		int o = 200;
		print("test 4 vrai\n");
		print(o);
	}
	
	else
	{
		print("test 4 faux\n");
	}
	
	print(k);
}
