1 eventloop with few classes and signals and slots between.

## BarberShop
owns the eventloop. Owns array of chairs.

### signals
#### customerAvailable (chair id)
#### noCustomerAvailable

### slots
#### customerArrived
checks for empty chairs, has customer sit, or increase missedCustomers counter
#### checkForAvailableCustomers
checks for waiting customers, emits customerAvailable if there is one, otherwise emits noCustomerAvailable
#### finishedWithCustomer (chair id)
empties char with id, increases servicedCustomers counter
#### close
stops customer spawner, prints final info, stops eventloop and exits the program


## CustomerSpawner
symbolizes new customers arraving (basically a timer)

### signals
#### customerArrives
emitted based on timer

### slots
#### stopSpawning
stops the timer

## Barber

### signals
#### customerFinished (chair id)
#### checkForCustomers
#### closeShop

### slots
#### startWorkingOnCustomer
starts the worktime timer, emits customerFinished when ready, then emits checkForCustomers
#### goToSleep
emits closeShop
