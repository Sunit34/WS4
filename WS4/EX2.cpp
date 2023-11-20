#include <iostream>
#include <string>

class Objet2D {
private:
    int dim1, dim2;
    Objet2D* Suivant;

public:
    Objet2D();
    Objet2D(int d1, int d2);
    virtual int GetPerimeter();
    virtual int GetAire();
    virtual std::string AfficheInfo();
    Objet2D* GetSuivant() const;
    void SetSuivant(Objet2D* suivant);
};

Objet2D::Objet2D() : dim1(0), dim2(0), Suivant(nullptr) {}

Objet2D::Objet2D(int d1, int d2) : dim1(d1), dim2(d2), Suivant(nullptr) {}

int Objet2D::GetPerimeter() {
    return 2 * (dim1 + dim2);
}

int Objet2D::GetAire() {
    return dim1 * dim2;
}

std::string Objet2D::AfficheInfo() {
    return "Objet2D";
}

Objet2D* Objet2D::GetSuivant() const {
    return Suivant;
}

void Objet2D::SetSuivant(Objet2D* suivant) {
    Suivant = suivant;
}

class Rectangle : public Objet2D {
private:
    int longueur, largeur;

public:
    Rectangle();
    Rectangle(int l, int w);
    int GetLongueur();
    int GetLargeur();
    virtual int GetPerimeter() override;
    virtual int GetAire() override;
    virtual std::string AfficheInfo() override;
};

class Cube : public Objet2D {
private:
    int cote;

public:
    Cube();
    Cube(int c);
    int GetCote();
    int GetPerimetre();
    int GetAire();
    std::string AfficheInfo() override;
};

class ListeObjets2D {
private:
    Objet2D* Head;
    Objet2D* Tail;

public:
    ListeObjets2D();
    ~ListeObjets2D(); // Destructeur pour libérer la mémoire
    void AjouterEnTete(Objet2D* objet);
    void AjouterEnQueue(Objet2D* objet);
    void AjouterAIndex(Objet2D* objet, int index);
    void SupprimerEnTete();
    void SupprimerEnQueue();
    void SupprimerAIndex(int index);
    void AfficherInfos();
};

ListeObjets2D::ListeObjets2D() : Head(nullptr), Tail(nullptr) {}

ListeObjets2D::~ListeObjets2D() {
    // Libérer la mémoire lors de la destruction de la liste
    while (Head != nullptr) {
        Objet2D* temp = Head;
        Head = Head->GetSuivant();
        delete temp;
    }
}

void ListeObjets2D::AjouterEnTete(Objet2D* objet) {
    objet->SetSuivant(Head);
    Head = objet;
    if (Tail == nullptr) {
        Tail = Head; // Si la liste était vide, la queue pointe également vers le nouvel objet
    }
}

void ListeObjets2D::AjouterEnQueue(Objet2D* objet) {
    if (Tail == nullptr) {
        Head = Tail = objet;
    } else {
        Tail->SetSuivant(objet);
        Tail = objet;
    }
}

void ListeObjets2D::AjouterAIndex(Objet2D* objet, int index) {
    if (index == 0) {
        AjouterEnTete(objet);
    } else {
        Objet2D* temp = Head;
        for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
            temp = temp->GetSuivant();
        }
        if (temp != nullptr) {
            objet->SetSuivant(temp->GetSuivant());
            temp->SetSuivant(objet);
            if (temp == Tail) {
                Tail = objet;
            }
        } else {
            std::cerr << "Index hors limites." << std::endl;
        }
    }
}

void ListeObjets2D::SupprimerEnTete() {
    if (Head != nullptr) {
        Objet2D* temp = Head;
        Head = Head->GetSuivant();
        delete temp;
        if (Head == nullptr) {
            Tail = nullptr; // La queue est également mise à jour si la liste est vide après la suppression
        }
    } else {
        std::cerr << "La liste est vide." << std::endl;
    }
}

void ListeObjets2D::SupprimerEnQueue() {
    if (Head != nullptr) {
        if (Head == Tail) {
            delete Head;
            Head = Tail = nullptr;
        } else {
            Objet2D* temp = Head;
            while (temp->GetSuivant() != Tail) {
                temp = temp->GetSuivant();
            }
            delete Tail;
            Tail = temp;
            Tail->SetSuivant(nullptr);
        }
    } else {
        std::cerr << "La liste est vide." << std::endl;
    }
}

void ListeObjets2D::SupprimerAIndex(int index) {
    if (index == 0) {
        SupprimerEnTete();
    } else {
        Objet2D* temp = Head;
        for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
            temp = temp->GetSuivant();
        }
        if (temp != nullptr && temp->GetSuivant() != nullptr) {
            Objet2D* aSupprimer = temp->GetSuivant();
            temp->SetSuivant(aSupprimer->GetSuivant());
            if (aSupprimer == Tail) {
                Tail = temp;
            }
            delete aSupprimer;
        } else {
            std::cerr << "Index hors limites." << std::endl;
        }
    }
}

void ListeObjets2D::AfficherInfos() {
    Objet2D* temp = Head;
    while (temp != nullptr) {
        std::cout << temp->AfficheInfo() << std::endl;
        temp = temp->GetSuivant();
    }
}

int main() {
    ListeObjets2D liste;

    // Ajout d'objets à la classe de stockage jusqu'à ce que l'utilisateur le souhaite
    char continuer;
    do {
        int choix;
        std::cout << "Choisissez le type d'objet : \n";
        std::cout << "1. Rectangle\n";
        std::cout << "2. Cube\n";
        std::cout << "Votre choix : ";
        std::cin >> choix;

        if (choix == 1) {
            int longueur, largeur;
            std::cout << "Entrez la longueur du rectangle : ";
            std::cin >> longueur;
            std::cout << "Entrez la largeur du rectangle : ";
            std::cin >> largeur;

            Objet2D* nouvelObjet = new Rectangle(longueur, largeur);
            liste.AjouterEnQueue(nouvelObjet);
        } else if (choix == 2) {
            int cote;
            std::cout << "Entrez la longueur du côté du cube : ";
            std::cin >> cote;

            Objet2D* nouvelObjet = new Cube(cote);
            liste.AjouterEnQueue(nouvelObjet);
        } else {
            std::cerr << "Choix invalide.\n";
        }

        std::cout << "Voulez-vous ajouter un autre objet ? (O/N) : ";
        std::cin >> continuer;

    } while (continuer == 'O' || continuer == 'o');

    // Affichage des informations des objets stockés
    liste.AfficherInfos();

    // Libération de la mémoire
    Objet2D* temp = liste.GetHead();
    while (temp != nullptr) {
        Objet2D* suivant = temp->GetSuivant();
        delete temp;
        temp = suivant;
    }

    return 0;
}