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

let renderItem = (onPress) =>
  FlatList.renderItem(({item}) =>
    <TodoCell text=item.text finish=item.finish onValueChange=(_b => onPress(item)) />
  );

let make = (~name: string, _children) => {
  ...component,
  initialState: () => {tasks: [], toggle: false},
  reducer: (action, state) =>
    switch action {
    | ElseToggle(b) => ReasonReact.Update({...state, toggle: b})
    | Toggle(_b) => ReasonReact.Update({...state, tasks: [...state.tasks]})
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
        title="Learoeeere"
        color="#841584"
        accessibilityLabel="Learn more about this purple button"
        onPress=(
          _e =>
            self.send(
              UpserTask({
                key: string_of_int(List.length(self.state.tasks)),
                text: "hieegh",
                finish: false
              })
            )
        )
      />
      <FlatList
        renderItem=(renderItem( item => self.send(Toggle(item))))
        keyExtractor=((item, _) => item.key)
        data=(Array.of_list(self.state.tasks))
      />
    </View>
};
/* let make = (~name: string, _children) => {
     ...component, /* spread the template's other defaults into here  */
     initialState: () => { tasks: [||] },
     reducer: (action, state) =>
       switch (action) {
       | UpserTask(item) => ReasonReact.Update({...state, tasks: [|item, ...state.tasks]})
       | Keep => ReasonReact.Update({...state, tasks: [||]})
       },
     render: _self =>
       <View
         style=Style.(
                 style([flex(1.), justifyContent(Center), alignItems(Center)])
               )>
         <Button
           title="Learn More"
           color="#841584"
           accessibilityLabel="Learn more about this purple button"
           onPress=onButtonPress
         />
         <FlatList
           renderItem=(renderItem(b => self.send(Toggle(b))))
           keyExtractor=((item, _) => item.key)
           data={self.state.tasks}
         />
         <Text> (ReasonReact.stringToElement(name)) </Text>
       </View>
   }; */