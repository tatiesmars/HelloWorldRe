open BsReactNative;

Random.self_init();

let header = () => <View />;

let footer = () => <View />;

let app = () => 
  <Home title="My Todo List!!" />;
/* <View style=Style.(style([flex(1.)]))>
      <View style=Style.(style([flex(0.1), backgroundColor("#444")]))>
        <View> <Text> (ReasonReact.stringToElement("Header")) </Text> </View>
      </View>
      <View style=Style.(style([flex(0.8)]))> <Home name="Home" /> </View>
      <View style=Style.(style([flex(0.1), backgroundColor("#444")]))>
        <View> <Text> (ReasonReact.stringToElement("Footer")) </Text> </View>
      </View>
   <View style=Style.(style([justifyContent(Center), alignItems(Center)]))>
    </View>; */