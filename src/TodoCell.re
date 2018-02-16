open BsReactNative;

type state = bool;

type action =
  | ToggleEdit(bool);

let component = ReasonReact.reducerComponent("TodoCell");

let make =
    (~value: string, ~toggle: bool, ~onToggle, ~onDelete, ~onEdit, _children) => {
  ...component,
  initialState: () => false,
  reducer: (action, _state) =>
    switch action {
    | ToggleEdit(b) => ReasonReact.Update(b)
    },
  render: self =>
    <View>
        <EditButton value onEdit isEditing=self.state onSwitch=(b => self.send(ToggleEdit(b))) />
        <Text>(ReasonReact.stringToElement(string_of_bool(toggle))) </Text>
      <Switch value=toggle onValueChange=onToggle />
      <Button title="delete" color="#841584" onPress=(_e => onDelete()) />
    </View>
};

/* style=Style.(
  style([
    alignItems(Center),
    backgroundColor(!self.state ? "#AAA" : "#DDD"),
    padding(Pt(10.))
  ]) 
  )*/