#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char** argv) {

  if (argc < 2) {
    std::cout << "Please provide the XML file path as a command line argument." << std::endl;
    return 1;
  }

  char* xmlFilePath = argv[1];

  xmlInitParser();

  xmlDoc* doc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_DTD);
  if (doc == NULL) {
    std::cout << "Error parsing XML file: " << xmlFilePath << std::endl;
    return 1;
  }

  xmlNode* root = xmlDocGetRootElement(doc);
  if (root == NULL) {
    std::cout << "Error retrieving root element from XML document." << std::endl;
    xmlFreeDoc(doc);
    return 1;
  }

  xmlNode* child = root->children;
  while (child) {
    if (xmlStrcmp(child->name, (const xmlChar*)"book") == 0) {
      xmlNode* titleNode = xmlFirstElementChild(child,"title");
      if (titleNode != NULL) {
        std::cout << "Book Title: " << xmlNodeGetContent(titleNode) << std::endl;
      }
    }

    child = child->next;
  }

  xmlCleanupParser();
  xmlFreeDoc(doc);

  return 0;
}