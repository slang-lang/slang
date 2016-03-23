
public namespace IO
{
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

		public bool readBool() {
			bool value = freadb(mHandle);
			return value;
		}

		public double readDouble() {
			double value = freadd(mHandle);
			return value;
		}

		public float readFloat() {
			float value = freadf(mHandle);
			return value;
		}

		public int readInt() {
			int value = freadi(mHandle);
			return value;
		}

		public string readString(int length) {
			string value = freads(mHandle, length);
			return value;
		}

		public bool rewind() {
			int result = fseek(mHandle, 0);
			return (result == 0);
		}

		public bool seek(int address) {
			int result = fseek(mHandle, address);
			return (result == 0);
		}

		public bool write(bool value) {
			int result = fwriteb(mHandle, value);
			return (result == 0);
		}

		public bool write(double value) {
			int result = fwrited(mHandle, value);
			return (result == 0);
		}

		public bool write(float value) {
			int result = fwritef(mHandle, value);
			return (result == 0);
		}

		public bool write(int value) {
			int result = fwritei(mHandle, value);
			return (result == 0);
		}

		public bool write(string value) {
			int result = fwrites(mHandle, value);
			return (result == 0);
		}
	}
}

