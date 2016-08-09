
/* OUTPUT
Biggest Market Place in the World.
Simplest way to manage Money.
1st Web 2.0 Company.
1st Web 2.0 Company.
Google - biggest search giant.. ATT - my carrier provider..
*/
 
public object CrunchifyEnumExample {
 
	public enum Company {
		EBAY,
		PAYPAL,
		GOOGLE,
		YAHOO,
		ATT
	}
 
	private Company mName;
 
	public CrunchifyEnumExample(Company name) {
		mName = name;
	}
 
	public void companyDetails() {
		switch ( mName ) {
			case EBAY: {
				writeln("Biggest Market Place in the World.");
				break;
			}
			case PAYPAL: {
				writeln("Simplest way to manage Money.");
				break;
			}
			case GOOGLE: {
				writeln("1st Web 2.0 Company.");
				continue;
			}
			case YAHOO: {
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
	public void main(int argc, string args) {
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
