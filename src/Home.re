open BsReactNative;

type item = {
  key: string,
  text: string,
  finish: bool
};

type state = {
  tasks: list(item),
  toggle: bool
};

type action =
  | UpserTask(item)
  | Toggle(item)
  | ElseToggle(bool);

let onButtonPress = v => Alert.alert(~title={j|你好，$v|j}, ());

let component = ReasonReact.reducerComponent("Home");

let renderItem = onPress =>
  FlatList.renderItem(({item}) =>
    <TodoCell
      text=item.text
      finish=item.finish
      onValueChange=(b => onPress({...item, finish: b}))
    />
  );

let make = (~name: string, _children) => {
  ...component,
  initialState: () => {tasks: [], toggle: false},
  reducer: (action, state) =>
    switch action {
    | ElseToggle(b) => ReasonReact.Update({toggle: b, tasks: []})
    | Toggle(i) => ReasonReact.Update({...state, tasks: [i, ...List.filter(x => x.key !== i.key,state.tasks)]})
    | UpserTask(i) =>
      ReasonReact.Update({...state, tasks: [i, ...state.tasks]})
    },
  render: self =>
    <View
      style=Style.(
              style([flex(1.), justifyContent(Center), alignItems(Center)])
            )>
      <TodoCell
        text=name
        finish=self.state.toggle
        onValueChange=(b => self.send(ElseToggle(b)))
      />
      <Button
        title="Learefaefaeoeeere"
        color="#841584"
        onPress=(
          _e =>
            self.send(
              UpserTask({
                key: string_of_int(List.length(self.state.tasks)),
                text: "hieegh key: " ++ string_of_int(List.length(self.state.tasks)),
                finish: false
              })
            )
        )
      />
      <FlatList
        renderItem=(renderItem(item => self.send(Toggle(item))))
        keyExtractor=((item, _) => item.key)
        data=(Array.of_list(self.state.tasks))
      />
    </View>
};