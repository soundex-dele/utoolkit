#include <gtest/gtest.h>
#include <utoolkit/utils/file_utils.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

using namespace utoolkit::utils;

class FileUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_dir = "test_directory";
        test_file = "test_file.txt";
        
        if (fs::exists(test_dir)) {
            fs::remove_all(test_dir);
        }
        if (fs::exists(test_file)) {
            fs::remove(test_file);
        }
    }
    
    void TearDown() override {
        if (fs::exists(test_dir)) {
            fs::remove_all(test_dir);
        }
        if (fs::exists(test_file)) {
            fs::remove(test_file);
        }
    }
    
    std::string test_dir;
    std::string test_file;
};

TEST_F(FileUtilsTest, FileExists) {
    EXPECT_FALSE(FileUtils::exists(test_file));
    
    std::ofstream file(test_file);
    file << "test content";
    file.close();
    
    EXPECT_TRUE(FileUtils::exists(test_file));
    EXPECT_TRUE(FileUtils::is_file(test_file));
    EXPECT_FALSE(FileUtils::is_directory(test_file));
}

TEST_F(FileUtilsTest, DirectoryExists) {
    EXPECT_FALSE(FileUtils::exists(test_dir));
    
    EXPECT_TRUE(FileUtils::create_directory(test_dir));
    EXPECT_TRUE(FileUtils::exists(test_dir));
    EXPECT_TRUE(FileUtils::is_directory(test_dir));
    EXPECT_FALSE(FileUtils::is_file(test_dir));
}

TEST_F(FileUtilsTest, CreateDirectories) {
    std::string nested_dir = FileUtils::join_path(test_dir, "nested/subdir");
    
    EXPECT_TRUE(FileUtils::create_directories(nested_dir));
    EXPECT_TRUE(FileUtils::exists(nested_dir));
    EXPECT_TRUE(FileUtils::is_directory(nested_dir));
}

TEST_F(FileUtilsTest, FileOperations) {
    std::string content = "Hello, World!";
    
    EXPECT_TRUE(FileUtils::write_file(test_file, content));
    EXPECT_TRUE(FileUtils::exists(test_file));
    
    std::string read_content;
    EXPECT_TRUE(FileUtils::read_file(test_file, read_content));
    EXPECT_EQ(read_content, content);
    
    std::string append_content = "\nAdditional content";
    EXPECT_TRUE(FileUtils::append_file(test_file, append_content));
    
    EXPECT_TRUE(FileUtils::read_file(test_file, read_content));
    EXPECT_EQ(read_content, content + append_content);
    
    EXPECT_TRUE(FileUtils::remove_file(test_file));
    EXPECT_FALSE(FileUtils::exists(test_file));
}

TEST_F(FileUtilsTest, PathManipulation) {
    std::string path = "/home/user/documents/file.txt";
    
    EXPECT_EQ(FileUtils::get_filename(path), "file.txt");
    EXPECT_EQ(FileUtils::get_directory(path), "/home/user/documents");
    EXPECT_EQ(FileUtils::get_extension(path), "txt");
    EXPECT_EQ(FileUtils::get_basename(path), "file");
}

TEST_F(FileUtilsTest, JoinPath) {
    EXPECT_EQ(FileUtils::join_path("/home/user", "documents"), "/home/user/documents");
    EXPECT_EQ(FileUtils::join_path("/home/user/", "documents"), "/home/user/documents");
    EXPECT_EQ(FileUtils::join_path("/home/user", "/documents"), "/home/user/documents");
}

TEST_F(FileUtilsTest, ListFilesAndDirectories) {
    EXPECT_TRUE(FileUtils::create_directories(test_dir));
    
    std::string file1 = FileUtils::join_path(test_dir, "file1.txt");
    std::string file2 = FileUtils::join_path(test_dir, "file2.txt");
    std::string subdir = FileUtils::join_path(test_dir, "subdir");
    
    FileUtils::write_file(file1, "content1");
    FileUtils::write_file(file2, "content2");
    FileUtils::create_directory(subdir);
    
    std::vector<std::string> files = FileUtils::list_files(test_dir);
    std::vector<std::string> dirs = FileUtils::list_directories(test_dir);
    
    EXPECT_GE(files.size(), 2);
    EXPECT_GE(dirs.size(), 1);
}

TEST_F(FileUtilsTest, FileSize) {
    std::string content = "This is a test file content";
    FileUtils::write_file(test_file, content);
    
    uint64_t size = FileUtils::get_file_size(test_file);
    EXPECT_EQ(size, content.length());
}

TEST_F(FileUtilsTest, CurrentWorkingDirectory) {
    std::string cwd = FileUtils::get_current_working_directory();
    EXPECT_FALSE(cwd.empty());
    EXPECT_TRUE(FileUtils::exists(cwd));
    EXPECT_TRUE(FileUtils::is_directory(cwd));
}