# Singleton

Ziel dieser Seite ist es, den Befriff Singleton für das Assignement so weit zu erklären, dass Singletons verstanden und für den gewünschten Zweck verwendet werden können. Genauere Infos über Singletons in C++, können selbständig in Büchern oder im Internet recherchiert werden.

## Algemein

Ein Singleton stellt sicher, dass es nur genau ein Objekt einer Klasse gibt. Wird eine Klasse also als Singleton implementiert, so kann es nicht mehr als eine Instanz der Klasse geben.

## Beispiel ein Singleton Klasse

```C++
#ifndef TEST_SINGLETONCLASS_H
#define TEST_SINGLETONCLASS_H

class SingletonClass
{
  public:
    static SingletonClass& instance()
    {
       static SingletonClass instance_;
       return instance_;
    }
    ~ SingletonClass() {}
    void function();
  private:
    SingletonClass() :variable(20) {}
    SingletonClass( const SingletonClass& ); 
    SingletonClass& operator = (const SingletonClass&); 

    int variable;
};
#endif
```

Dadurch, dass Konstruktor, Copy-Konstruktor und Copy-Assignment-Operator`private` sind, kann eine Instanz von `SingletonClass` nur innerhalb dieser Klasse erstellt werden. Von außen kann ein `SingletonClass`-Objekt über die `static`-Methode `instance` angefordert werden. Auch bei wiederholten Aufrufen von `instance` wird immer die selbe Instanz zurückgegeben.

## Verwendung der Klasse

Um die Singleton Klasse zu verwenden kann entweder die Instanz als Referenz verwendet werdenoder direkt auf die Instanz verwendet werden.

```C++
SingletonClass &singleton = SingletonClass::instance();
singleton.function();
// oder dierekte Verwendung
SingletonClass::instance().function();
```

Um die Singleton Klasse zu verwenden muss diese lediglich inkludiert werden. Sobald diese irgendwo inkludiert und verwendet wurde wird auch eine Instanz dafür angelegt.
