open BsReactNative;

let component = ReasonReact.statelessComponent("TodoCell");

let make = (
  ~text: string,
  ~finish: bool,
  ~onValueChange: (bool) => unit,
  _children) => {
  ...component,
  render: _self =>
  <View>
      <Text> (ReasonReact.stringToElement(text)) </Text>        
      <Switch value=finish onValueChange/>
  </View>
};


/* switch (List.find((i) => i === theItem, myItems)) {
  | item => print_endline(item)
  | exception Not_found => print_endline("No such item found!")
  }; */
/* 
  reducer: (action, state) =>
  switch (action) {
  | Click => ReasonReact.Update({...state, count: state.count + 1})
  | Toggle => ReasonReact.Update({...state, show: ! state.show})
  }, */