/*  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#ifndef GLOBALHELPER_HH
#define GLOBALHELPER_HH

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QString>
#include <memory>

class QCoreApplication;

class GlobalParser {

private:

  static GlobalParser* _self;

  static QCommandLineParser clParser;

  static QCommandLineOption helpOption;
  static QCommandLineOption versionOption;

  static QCommandLineOption testOption;
  static QCommandLineOption portOption;

public:


  

public:

  GlobalParser();
  ~GlobalParser();

  static bool isSet(const QCommandLineOption& opt);

  static QString value(const QCommandLineOption& opt);

  static void process(const QCoreApplication & app);

  inline const static QCommandLineOption help_option() { return helpOption; }
  inline const static QCommandLineOption version_option() { return versionOption; }
  inline const static QCommandLineOption test_option() { return testOption; }
  inline const static QCommandLineOption port_option() { return portOption; }


};

#endif