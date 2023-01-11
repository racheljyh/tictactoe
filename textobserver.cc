#include "textobserver.h"
#include <iostream>

using namespace std;

TextObserver::TextObserver(Game *g) : subject{g} {
    subject->attach(this);
}

TextObserver::~TextObserver() {
    subject->detach(this);
}

void TextObserver::notify() {
    for (int i = 1; i < subject->board()->getDimension(); ++ i) {
        cout << "       ";
        for (int j = 1; j < subject->board()->getDimension(); ++j) {
            cout << "|     ";
        }
        cout << endl;
        if (i > 9) { cout << i << "  "; }
        else { cout << i << "   "; }
        for (int k = 0; k < subject->board()->getDimension() - 1; ++k) {
            cout << subject->getState(i - 1, k) << "  |  ";
        }
        cout << subject->getState(i - 1, subject->board()->getDimension() - 1) << endl;
        cout << "  _ _ _";
        for (int l = 0; l < subject->board()->getDimension() - 1; ++l) {
            cout << "|_ _ _";
        }
        cout << endl;
    }

    cout << "       ";
    for (int j = 1; j < subject->board()->getDimension(); ++j) {
        cout << "|     ";
    }
    cout << endl;

    if (subject->board()->getDimension() > 9) { cout << subject->board()->getDimension() << "  "; } 
    else { cout << subject->board()->getDimension() << "   "; }
    for (int k = 0; k < subject->board()->getDimension() - 1; ++k) {
        cout << subject->getState(subject->board()->getDimension() - 1, k) << "  |  ";
    }
    cout << subject->getState(subject->board()->getDimension() - 1, subject->board()->getDimension() - 1) << endl;
    cout << "       ";
    for (int l = 0; l < subject->board()->getDimension() - 1; ++l) {
        cout << "|     ";
    }
    cout << endl;

    cout << "    a";
    for (int i = 1; i < subject->board()->getDimension(); ++i) {
        char colLetter = static_cast<char>(i + 97);
        cout << "     " << colLetter;
    }
    cout << endl;
}
