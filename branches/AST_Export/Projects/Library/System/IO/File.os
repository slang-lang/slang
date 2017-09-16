
import System.Exception;

public namespace System {
public namespace IO {

	public object File {
		private string mAccessMode;
		private string mFilename;
		private int mHandle;

		public void Constructor() {
			cleanup();
		}

		public void Constructor(string filename, string mode) {
			cleanup();

			open(filename, mode);
		}

		public void Destructor() {
			close();
		}

		private void cleanup() modify {
			mAccessMode = "";
			mFilename = "";
			mHandle = 0;
		}

		public bool close() modify {
			if ( !mHandle ) {
				return true;
			}

			int result = fclose(mHandle);

			cleanup();

			return (result == 0);
		}

		public bool isEOF() const {
			return feof(mHandle);
		}

		public bool isOpen() const {
			return (mHandle != 0);
		}

		public bool open(string filename, string mode) modify throws {
			if ( mHandle ) {
				// we already have an open file handle
				throw new Exception("file descriptor still points to an open file!");
			}

			mAccessMode = mode;
			mFilename = filename;
			mHandle = fopen(mFilename, mAccessMode);

			return (mHandle != 0);
		}

		public bool readBool() const {
			return freadb(mHandle);
		}

		public double readDouble() const {
			return freadd(mHandle);
		}

		public float readFloat() const {
			return freadf(mHandle);
		}

		public int readInt() const {
			return freadi(mHandle);
		}

		public string readString(int length = 1) {
			return freads(mHandle, length);
		}

		public bool rewind() const {
			return (fseek(mHandle, 0) == 0);
		}

		public bool seek(int address) {
			return (fseek(mHandle, address) == 0);
		}

		public bool write(bool value) {
			return (fwriteb(mHandle, value) == 0);
		}

		public bool write(double value) {
			return (fwrited(mHandle, value) == 0);
		}

		public bool write(float value) {
			return (fwritef(mHandle, value) == 0);
		}

		public bool write(int value) {
			return (fwritei(mHandle, value) == 0);
		}

		public bool write(string value) {
			return (fwrites(mHandle, value) == 0);
		}
	}
}
}

