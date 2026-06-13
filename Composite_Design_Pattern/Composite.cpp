// //
// // Created by shiva on 14-06-2026.
// //
// 📁 Root
//   📁 Documents
//     📄 resume.pdf
//     📄 notes.txt
//   📁 Photos
//     📄 pic1.jpg
//     📄 pic2.jpg
//   📄 readme.txt
//
// Root ka size = Documents ka size + Photos ka size + readme.txt ka size
//
// Documents ka size = resume.pdf + notes.txt
// Photos ka size = pic1.jpg + pic2.jpg
//
// Root.getSize()
// ↓
// Documents.getSize() + Photos.getSize() + readme.txt.getSize()
// ↓
// (resume.pdf + notes.txt) + (pic1.jpg + pic2.jpg) + 10
// ↓
// (100 + 50) + (200 + 150) + 10
// ↓
// 510

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IFileSystem {
public:
    virtual int getSize() = 0;
    virtual void display(int indent = 0) = 0;
    virtual ~IFileSystem() {}
};

class File : public IFileSystem {
    string name;
    int size;
public:
    File(string n, int s) {
        name = n;
        size = s;
    }
    int getSize() override {
        return size;
    }
    void display(int indent = 0) override {
        cout << string(indent, ' ') << "file " << name << " [" << size << " KB]" << endl;
    }
};
//indent for spacing.
// File f("resume.pdf", 100);
// f.getSize()     → 100
// f.display(0)    → 📄 resume.pdf [100 KB]
// f.display(4)    →     📄 resume.pdf [100 KB]

class Folder : public IFileSystem {
    string name;
    vector<IFileSystem*> children;
public:
    Folder(string n) {
        name = n;
    }
    void add(IFileSystem* item) {
        children.push_back(item);
    }
    int getSize() override {
        int total = 0;
        for(auto* child : children) {
            total += child->getSize();
        }
        return total;
    }
    void display(int indent = 0) override {
        cout << string(indent, ' ') << "FOLDER " << name << " [" << getSize() << " KB]" << endl;
        for(auto* child : children) {
            child->display(indent + 4);
        }
    }
};

// Documents.getSize()
// → resume.pdf.getSize() = 100
// → notes.txt.getSize()  = 50
// → total = 150
//
// Root.getSize()
// → Documents.getSize() = 150
// → Photos.getSize()    = 350
// → readme.txt.getSize() = 10
// → total = 510

int main() {
    // Files banao
    File* resume = new File("resume.pdf", 100);
    File* notes = new File("notes.txt", 50);
    File* pic1 = new File("pic1.jpg", 200);
    File* pic2 = new File("pic2.jpg", 150);
    File* readme = new File("readme.txt", 10);

    // Folders banao
    Folder* documents = new Folder("Documents");
    Folder* photos = new Folder("Photos");
    Folder* root = new Folder("Root");

    // Documents mein files daalo
    documents->add(resume);
    documents->add(notes);

    // Photos mein files daalo
    photos->add(pic1);
    photos->add(pic2);

    // Root mein sab daalo
    root->add(documents);
    root->add(photos);
    root->add(readme);

    // Display karo
    cout << "--- File System ---" << endl;
    root->display();

    cout << "\n--- Sizes ---" << endl;
    cout << "Documents : " << documents->getSize() << " KB" << endl;
    cout << "Photos    : " << photos->getSize() << " KB" << endl;
    cout << "Root      : " << root->getSize() << " KB" << endl;

    return 0;
}