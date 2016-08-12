#!/usr/local/bin/oscript

/* OUTPUT
Biggest Market Place in the World.
Simplest way to manage Money.
1st Web 2.0 Company.
1st Web 2.0 Company.
Google - biggest search giant.. ATT - my carrier provider..
*/

        public enum Company {
                EBAY = 0,
                PAYPAL = 1,
                GOOGLE = 2,
                YAHOO = 3,
                ATT = 4
        }


public object CrunchifyEnumExample {
/*
	public enum Company {
		EBAY,
		PAYPAL,
		GOOGLE,
		YAHOO,
		ATT
	}
*/
 
	private Company mName;
 
	public void CrunchifyEnumExample(int name) {
		writeln("CrunchifyEnumExample(" + name + ")");

		mName = name;
	}
 
	public void companyDetails() {
		writeln("companyDetails");

		switch ( mName ) {
			case Company.EBAY: {
				writeln("Biggest Market Place in the World.");
				break;
			}
			case Company.PAYPAL: {
				writeln("Simplest way to manage Money.");
				break;
			}
			case Company.GOOGLE: {
				writeln("1st Web 2.0 Company.");
				continue;
			}
			case Company.YAHOO: {
				writeln("1st Web 2.0 Company.");
				break;
			}
			default: {
				writeln("Google - biggest search giant.. ATT - my carrier provider..");
				break;
			}
		}
	}
}

public object Main {
	public void Main(int argc, string args) {
		CrunchifyEnumExample ebay = new CrunchifyEnumExample(Company.EBAY);
		ebay.companyDetails();

		CrunchifyEnumExample paypal = new CrunchifyEnumExample(Company.PAYPAL);
		paypal.companyDetails();

		CrunchifyEnumExample google = new CrunchifyEnumExample(Company.GOOGLE);
		google.companyDetails();

		CrunchifyEnumExample yahoo = new CrunchifyEnumExample(Company.YAHOO);
		yahoo.companyDetails();

		CrunchifyEnumExample att = new CrunchifyEnumExample(Company.ATT);
		att.companyDetails();
	}
}
