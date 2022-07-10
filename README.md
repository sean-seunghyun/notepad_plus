
# Notepad++++

Established Windows’ program by referring to Windows’ basic notepad program using C++ and MFC. 

Achieved features equivalent to Windows’ such as text-editing, scroll, search, undo, etc without using external text-editing
library. 

Added more advanced features like multiple undos and redos which windows’ notepad does not provide.

Furthered its text editor which can be able to be applied in other applications.

## Screenshots

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FfO5-5CC6FM.png?alt=media&token=2cdb7f6c-f90e-49b8-a1b7-5f34a54e9087)

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FAxZVVZG_tg.png?alt=media&token=554ed259-f4ba-4b11-8a43-19cfb274c27c)

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2F3gcw_h0_Te.png?alt=media&token=7d898822-098e-419c-bed4-7a516a6d4e4f)

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2F-0QlTClLwe.png?alt=media&token=6f17f535-8af1-4e2b-8e3c-d168373eae6c)

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FLh0k9H9mdE.png?alt=media&token=a10d39f4-cff3-45cf-ab2b-f0633fc53309)

## Description
This project was carried out in accordance with the following procedures.

### 1. Use Case Design

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FxnlnHgYzye.png?alt=media&token=48c60507-bdf6-458c-9d97-852dc8a9ef6c)

In the stage of use case design, the key functions necessary to create a notepad program were categorized into 25 types and charted as a use case diagram.

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FACvHwe-9py.png?alt=media&token=bf1dc9bd-5b27-44b9-9898-a1ed52f7834a)
About the core features of each of the 25 use cases, I wrote a use case scenario.

### 2. Object-Oriented Programming Design

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FW59e_GdJqm.jpg?alt=media&token=96d7af5d-068f-4d8b-9daa-898876fcaf30)
This is the simple OOP design diagram.
Since this program has a lot of features, this diagram helped me a lot to systematize its structure

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FkrVRNC2qa-.png?alt=media&token=7591cf05-091a-42cd-aeca-535762199781)

This is a core part of the OOP design.

I spent enough time for a design process so that I can clear its structure.

I used array type that I implemented myself so that I can learn its data structure and customize it easily.

I used composite pattern here to control the data consistently using class 'Glyph'
![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2Ft4hyB9TU-r.jpg?alt=media&token=438ee910-df40-4942-b7bf-0b0ec7fbd655)

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FTlq3TcLXqz.jpg?alt=media&token=95a130ea-6781-4c5f-9b9c-cf8c97029040)

This is the OOP design part that I used factory method pattern and command pattern.

![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2FSeanKim%2FvBRSPag7jK.png?alt=media&token=7a33dc34-8121-40b6-bf15-ba0e60e1a572)

In addition, observer pattern was also applied to update caret, scroll when there was an update of its note.


## Remark

The notepad I made was implemented one by one following its stage without using an existing library, so many things were vague. 

Throughout the project, I tried to follow the programming procedures I had been taught.

I was able to refer to the codes online, but I tried to rule them out as much as possible because they were a hindrance rather than a help to the overall program design.

Starting from understanding the problem, I was able to experience the realization of notepad while faithfully following the object-oriented design and interface design stages.

In the future, whenever I make a program, I try to follow these procedures and proceed with the design.