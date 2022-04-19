#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "observer.h"

namespace stratego {
/**
 * @brief The Observable class //todo
 */
class Observable {
public:
    /**
     * @brief addObserver //todo
     * @param observer
     */
    virtual void addObserver(Observer * observer) = 0;
    /**
     * @brief removeObserver //todo
     * @param observer
     */
    virtual void removeObserver(Observer * observer) = 0;
    /**
     * @brief notifyObserver //todo
     */
    virtual void notifyObserver() = 0;
};
}

#endif // OBSERVABLE_H
