open BsReactNative;

let component = ReasonReact.statelessComponent("TodoCell");

let make =
    (~text: string, ~finish: bool, ~onValueChange: bool => unit, _children) => {
  ...component,
  render: _self =>
    <View>
      <Text> (ReasonReact.stringToElement(text)) </Text>
      <Switch value=finish onValueChange />
    </View>
};
/* ReasonReact.Update({...state, tasks: [i, List.filter(item => item.key != i.key ,state.tasks]}) */