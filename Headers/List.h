class ListItem{
    public:
        ListItem *next = 0x0, *prev = 0x0;
        void* obj;

    ListItem(void *_obj){
        obj = _obj;
    }

    ~ListItem(){
    }
};

class List{
    public:
        unsigned int size = 0;
        ListItem *head, *tail;

        void Add(void *_obj){
            ListItem *i = new ListItem(_obj);
            if (head==0x0){
                head = i;
                tail = i;
            }
            else{
                i->next = head;
                head->prev = i;
                head = i;
            }
            size++;
        }

        void Remove(ListItem *i){
            if (i==tail){
                tail = i->prev;
                tail->next = 0x0;
            }
            else if (i==head) {
                head = i->next;
                head->prev = 0x0;
            }
            else{
                i->next->prev = i->prev;
                i->prev->next = i->next;
            }
        }
};