open BsReactNative;
let component = ReasonReact.statelessComponent("Celo");
let make = (~name: string, _children) => {
  ...component, /* spread the template's other defaults into here  */
  render: _self =>
    <View
      style=Style.(
              style([flex(1.), justifyContent(Center), alignItems(Center)])
            )>
      <Text> (ReasonReact.stringToElement(name)) </Text>
    </View>
};