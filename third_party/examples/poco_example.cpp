#include <iostream>
#include <Poco/Version.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <sstream>

#ifdef UTOOLKIT_ENABLE_POCO

void demonstrate_poco_version() {
    std::cout << "=== POCO Version Information ===" << std::endl;
    
    int version = POCO_VERSION;
    int major = (version >> 24) & 0xFF;
    int minor = (version >> 16) & 0xFF;
    int patch = (version >> 8) & 0xFF;
    int build = version & 0xFF;
    
    std::cout << "POCO Version: " << major << "." << minor << "." << patch << "." << build << std::endl;
}

void demonstrate_poco_datetime() {
    std::cout << "\n=== POCO DateTime ===" << std::endl;
    
    Poco::DateTime now;
    std::string formatted = Poco::DateTimeFormatter::format(now, "%Y-%m-%d %H:%M:%S");
    std::cout << "Current time: " << formatted << std::endl;
    
    Poco::DateTime tomorrow = now + Poco::Timespan(1, 0, 0, 0, 0);
    std::string tomorrow_str = Poco::DateTimeFormatter::format(tomorrow, "%Y-%m-%d");
    std::cout << "Tomorrow: " << tomorrow_str << std::endl;
}

void demonstrate_poco_path() {
    std::cout << "\n=== POCO Path ===" << std::endl;
    
    Poco::Path path("/usr/local/bin/example");
    std::cout << "Path: " << path.toString() << std::endl;
    std::cout << "Directory: " << path.parent().toString() << std::endl;
    std::cout << "Filename: " << path.getFileName() << std::endl;
    std::cout << "Extension: " << path.getExtension() << std::endl;
}

void demonstrate_poco_file() {
    std::cout << "\n=== POCO File ===" << std::endl;
    
    try {
        Poco::File current_dir(".");
        std::cout << "Current directory: " << current_dir.path() << std::endl;
        std::cout << "Is directory: " << (current_dir.isDirectory() ? "Yes" : "No") << std::endl;
        std::cout << "Exists: " << (current_dir.exists() ? "Yes" : "No") << std::endl;
        
        Poco::File temp_file("temp_test.txt");
        if (!temp_file.exists()) {
            std::ofstream ofs("temp_test.txt");
            ofs << "POCO file test";
            ofs.close();
        }
        
        std::cout << "Temp file size: " << temp_file.getSize() << " bytes" << std::endl;
        
        // 清理
        if (temp_file.exists()) {
            temp_file.remove();
        }
    } catch (const Poco::Exception& e) {
        std::cout << "File operation error: " << e.displayText() << std::endl;
    }
}

int main() {
    std::cout << "μToolkit POCO Library Demonstration" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    demonstrate_poco_version();
    demonstrate_poco_datetime();
    demonstrate_poco_path();
    demonstrate_poco_file();
    
    std::cout << "\nPOCO demonstration completed successfully!" << std::endl;
    return 0;
}

#else

int main() {
    std::cout << "POCO library is not enabled in this build." << std::endl;
    std::cout << "Please enable UTOOLKIT_ENABLE_POCO to use POCO features." << std::endl;
    return 0;
}

#endif