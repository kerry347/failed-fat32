#pragma once
#include <cstdint>
#include <fstream>

enum class EntryType { main = 0, sub };

class DirEntry {
 public:
  virtual void Read(char buf[32]) = 0;
  virtual void Write(std::ofstream &file) = 0;
  virtual bool isEmpty() = 0;
  EntryType entryType;
  static bool isMain(char buf[32]);
  DirEntry(EntryType _entryType) : entryType(_entryType) {}
};

enum class EntryAttribute : uint8_t { empty = 0, file, dir, pass, dirpass };

class MainEntry : public DirEntry {
 public:
  MainEntry(char buf[32]) : DirEntry(EntryType::main) { Read(buf); };

  void Init(char shortName[11], EntryAttribute _att, uint32_t fSize);
  void Read(char buf[32]);
  void Write(std::ofstream &fo);
  bool isEmpty();

  uint8_t filename[8];       // 8
  uint8_t extension[3];      // 3
  EntryAttribute attribute;  // 1
  char useless[10];          // 10
  uint16_t modifiedTime;     // 2
  uint16_t modifiedDate;     // 2
  uint16_t firstCluster;     // 2
  uint32_t fileSize;         // 4
};

class SubEntry : public DirEntry {
 public:
  SubEntry(char buf[32]) : DirEntry(EntryType::sub) { Read(buf); }
  void Read(char buf[32]);
  void Write(std::ofstream &fo);
  bool isEmpty();
  void InitName(char16_t *_name, uint8_t nb, int length = 10);

  uint8_t sequence_number_name = 0;  // 6 bit luu so thu tu, 2 bit ket thuc
  uint8_t pass[10];
  uint8_t const signature = 0xF;  // TODO
  wchar_t name[10];
};
