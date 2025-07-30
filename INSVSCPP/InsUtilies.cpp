#include<iostream>
#include<sstream>
using namespace std;

namespace InsUtilies {
	/// <summary>
	/// 游程编码压缩
	/// </summary>
	/// <param name="input">输入字符串</param>
	/// <returns>压缩后的字符串</returns>
	string RLEZip(const string& input) {
		try {
			ostringstream oss;
			for (size_t i = 0; i < input.size(); ++i) {
				size_t count = 1;
				while (i + count < input.size() && input[i] == input[i + count]) count++;
				oss << input[i] << count;
			}

			return oss.str();
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 游程编码解压缩
	/// </summary>
	/// <param name="input">输入字符串</param>
	/// <returns>解压缩后的字符串</returns>
	string RLEUnzip(const string& input) {
		try {
			string output;
			size_t i = 0;
			while (i < input.length()) {
				char ch = input[i++];
				string countStr;
				while (i < input.size()&& isdigit(input[i])) {
					countStr += input[i++];
				}
				int count = stoi(countStr);
				output.append(count, ch);
			}

			return output;
		}
		catch (exception e) {

		}
	}
}