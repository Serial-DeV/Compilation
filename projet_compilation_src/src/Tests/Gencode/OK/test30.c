
void main()
{
	int k = 15;
	int l = 15;
	int n = 12;
	bool o = true;
	bool p = true;

	if(p != o)
	{
		int k = 10;
		print("test 1 vrai");
		print(k);
		int c = 0;
		bool b = true;

		while(n < 2 * k)
		{
			n = n + 1;
			b = !b;
			c = c + 1;
			print(c);
			print(b);
			print(n);
			if(b)
			{
				int l = 458;
				c = c * c;
				print(l);
			}
		}
		
	}
	
	else
	{
		print("test 1 faux");
	}
	
	if(k < 12+1)
	{
		int o = 50;
		print("test 2 vrai");
		print(o);
	}
	
	else
	{
		int i;
		for(i = 0; i < 10; i = i + 1)
		{
			print(i);
			print("test 2 faux");
		}
	}

	
	print(o);
}
