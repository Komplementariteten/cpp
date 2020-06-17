#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic* _chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    //// STUDENT CODE
    ////
    ChatBot(const ChatBot &source); //  copy constructor
    ChatBot(ChatBot &&source); // Move

    ChatBot &operator=(const ChatBot &source) {
        std::cout << "Copy assignment" << std::endl;
        if (this == &source)
            return *this;

        if(_image != NULL) {
            delete _image;
            _image = NULL;
        }
        *_image = *source._image;
        _chatLogic = std::move(source._chatLogic);
        _rootNode = source._rootNode;
        return *this;
    }

    ChatBot &operator=(ChatBot &&source) {
        std::cout << "Move assignment" << std::endl;
        if (this == &source)
            return *this;
        delete _image;
        _image = source._image;
        _chatLogic = std::move(source._chatLogic);
        _rootNode = source._rootNode;
        source._chatLogic = nullptr;
        source._rootNode = nullptr;
        return *this;
    }

    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */