open BsReactNative;

type item = {
  key: string,
  text: string,
  order: int,
  finish: bool
};

type state = {
  tasks: list(item),
  toggle: bool
};

type action =
  | UpserTask(item)
  | DeleteTask(item)
  | ElseToggle(bool);

let onButtonPress = v => Alert.alert(~title={j|你好，$v|j}, ());

let component = ReasonReact.reducerComponent("Home");

let renderItem = (onPress, onDelete, onEdit) =>
  FlatList.renderItem(({item}) =>
    <TodoCell
      value=(item.text)
      toggle=item.finish
      onToggle=(b => onPress({...item, finish: b}))
      onDelete=(() => onDelete(item))
      onEdit=((s) => onEdit({...item, text: s}))
    />
  );

let make = (~name: string, _children) => {
  ...component,
  initialState: () => {tasks: [], toggle: false},
  reducer: (action, state) =>
    switch action {
    | ElseToggle(b) => ReasonReact.Update({toggle: b, tasks: []})
    | DeleteTask(i) =>
      ReasonReact.Update({
        ...state,
        tasks: List.filter(x => x.key !== i.key, state.tasks)
      })
    | UpserTask(i) =>
      ReasonReact.Update({
        ...state,
        tasks: [i, ...List.filter(x => x.key !== i.key, state.tasks)]
      })
    },
  render: self =>
    <View
      style=Style.(
              style([flex(1.), justifyContent(Center), alignItems(Center)])
            )>
      /* <TodoCell
           text=name
           finish=self.state.toggle
           onValueChange=(b => self.send(ElseToggle(b)))
         /> */

        <Button
          title=name
          color="#841584"
          onPress=(
            _e =>
              self.send(
                UpserTask({
                  key: string_of_int(Random.int(100000)),
                  order: List.length(self.state.tasks),
                  text:
                    "My task",
                  finish: false
                })
              )
          )
        />
        <Button
          title="add task"
          color="#841584"
          onPress=(
            _e =>
              self.send(
                UpserTask({
                  key: string_of_int(Random.int(100000)),
                  order: List.length(self.state.tasks),
                  text:
                    "My task",
                  finish: false
                })
              )
          )
        />
        <FlatList
          renderItem=(
            renderItem(
              item => self.send(UpserTask(item)),
              item => self.send(DeleteTask(item)),
              item => self.send(UpserTask(item))
            )
          )
          keyExtractor=((item, _) => item.key)
          data=(
            Array.of_list(
              List.sort((x, y) => x.order - y.order, self.state.tasks)
            )
          )
        />
      </View>
};