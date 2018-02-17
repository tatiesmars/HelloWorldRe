open BsReactNative;

let component = ReasonReact.statelessComponent("EditButton");

let make = (~value, ~isEditing, ~onEdit, ~onSwitch, _children) => {
  ...component,
  render: _self =>
    isEditing ?
      <TextInput onEndEditing=(() => onSwitch(false)) style=Style.(style([
        textAlign(Center),
        backgroundColor("#DDD"),
        padding(Pt(10.)),
        width(Pt(300.))
      ])) onChangeText=onEdit value=value /> :
            <TouchableOpacity
              onPress=(() => onSwitch(true))
        style=Style.(
                style([
                  alignItems(Center),
                  backgroundColor("#AAA"),
                  padding(Pt(10.)),
                  width(Pt(300.))
                ])
              )>
              <Text> (ReasonReact.stringToElement(value)) </Text>
      </TouchableOpacity>              
};