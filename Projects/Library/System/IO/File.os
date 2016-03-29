
public namespace System {
public namespace IO {

	public object File
	{
		private string mAccessMode;
		private string mFilename;
		private int mHandle;

		public void File() {
			mAccessMode = "";
			mFilename = "";
			mHandle = 0;
		}

		public void File(string filename, string mode) {
			open(filename, mode);
		}

		public void ~File() {
			if ( mHandle != 0 ) {
				close();
			}
		}

		public bool close() modify {
			print("File::close()");

			if ( mHandle == 0 ) {
				return false;
			}

			int result = fclose(mHandle);

			mAccessMode = "";
			mFilename = "";
			mHandle = 0;

			return (result == 0);
		}

		public int getDescriptor() const {
			return mHandle;
		}

		public bool isOpen() const {
			return (mHandle != 0);
		}

		public bool open(string filename, string mode) modify {
			print("File::open(\"" + filename + "\", \"" + mode + "\")");

			if ( mHandle != 0 ) {
				// we already have an open file handle
				throw new string("file descriptor still points to an open file!");
			}

			mAccessMode = mode;
			mFilename = filename;
			mHandle = fopen(mFilename, mAccessMode);

			return true;
		}

		public bool readBool() const {
			bool value = freadb(mHandle);
			return value;
		}

		public double readDouble() const {
			double value = freadd(mHandle);
			return value;
		}

		public float readFloat() const {
			float value = freadf(mHandle);
			return value;
		}

		public int readInt() const {
			int value = freadi(mHandle);
			return value;
		}

		public string readString(int length const) {
			string value = freads(mHandle, length);
			return value;
		}

		public bool rewind() const {
			int result = fseek(mHandle, 0);
			return (result == 0);
		}

		public bool seek(int address const) {
			int result = fseek(mHandle, address);
			return (result == 0);
		}

		public bool write(bool value const) {
			int result = fwriteb(mHandle, value);
			return (result == 0);
		}

		public bool write(double value const) {
			int result = fwrited(mHandle, value);
			return (result == 0);
		}

		public bool write(float value const) {
			int result = fwritef(mHandle, value);
			return (result == 0);
		}

		public bool write(int value const) {
			int result = fwritei(mHandle, value);
			return (result == 0);
		}

		public bool write(string value const) {
			int result = fwrites(mHandle, value);
			return (result == 0);
		}
	}
}
}

